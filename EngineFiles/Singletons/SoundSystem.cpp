#include "SoundSystem.h"
#include "ResourceManager.h"
#include <SDL_mixer.h>
#include <iostream>
#include <queue>

//////////////////////////////
/////////SDL SOUND SYSTEM
//////////////////////////////

amu::SDLSoundSystem::SDLSoundSystem() 
	: m_SoundPromise{ std::promise<void>() }
	, m_SoundFuture{ m_SoundPromise.get_future() }
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

amu::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_Quit();
	Mix_CloseAudio();
}

void amu::SDLSoundSystem::Update()
{
	while (not m_ShouldQuit)
	{
		m_SoundFuture.get();
		
		std::queue<SoundRequest> soundsToPlay{};

		m_SoundMutex.lock();

		while (not m_SoundRequestDeque.empty())
		{
			soundsToPlay.push(m_SoundRequestDeque.front());
			m_SoundRequestDeque.pop_front();
		}

		m_SoundPromise = std::promise<void>();
		m_SoundFuture = m_SoundPromise.get_future();
		m_IsScheduled = false;

		m_SoundMutex.unlock();

		while (not soundsToPlay.empty())
		{
			auto [id, volume, fileName] = soundsToPlay.front();
			PlaySoundEffect(id, volume, fileName);
			soundsToPlay.pop();
		}
	}
}

bool amu::SDLSoundSystem::RequestSoundEffect(int id, const std::string& filePath, int volume)
{
	std::lock_guard lockPlaying{ m_SoundMutex };

	if (bool hasFoundSimilar = std::any_of(m_SoundRequestDeque.begin(), m_SoundRequestDeque.end(),
		[&](SoundRequest& req)
		{
			if (req.ID == id)
			{
				req.Volume = std::max(req.Volume, volume);
				return true;
			}
			return false;
		}); hasFoundSimilar)
	{
		return false;
	}

	m_SoundRequestDeque.emplace_back(SoundRequest{ id, filePath, volume });

	if (not m_IsScheduled)
	{
		m_SoundPromise.set_value();
		m_IsScheduled = true;
	}

	return true;
}

void amu::SDLSoundSystem::SignalEnd()
{
	std::lock_guard close{ m_SoundMutex };

	m_ShouldQuit = true;
	if (not m_IsScheduled)
	{
		m_SoundPromise.set_value();
		m_IsScheduled = true;
	}
}

void amu::SDLSoundSystem::PlaySoundEffect(int id, const std::string& fileName, int volume)
{
	if (not m_SoundMap.contains(id))
	{
		m_SoundMap[id] = ResourceManager::GetInstance().LoadSoundEffect(fileName);
	}

	m_SoundMap[id]->PlaySoundEffect(volume);
}

//////////////////////////////
/////////LOG SOUND SYSTEM
//////////////////////////////

amu::LogSoundSystem::LogSoundSystem(std::unique_ptr<ISoundSystem>&& actualSoundSystemUPtr)
	: m_ActualSoundSystemUPtr{ std::move(actualSoundSystemUPtr) }
{
}

void amu::LogSoundSystem::Update()
{
	m_ActualSoundSystemUPtr->Update();
}

bool amu::LogSoundSystem::RequestSoundEffect(int id, const std::string& filePath, int volume)
{
	if (m_ActualSoundSystemUPtr->RequestSoundEffect(id, filePath, volume))
	{
		std::cout << "Requested sound id: " << id << " at volume " << volume << "\n";
		return true;
	}
	std::cout << "Sound added with id: " << id << " from dir " << filePath << "\n";

	return false;
}

void amu::LogSoundSystem::SignalEnd()
{
	m_ActualSoundSystemUPtr->SignalEnd();
	std::cout << "Sound execution should end\n";
}