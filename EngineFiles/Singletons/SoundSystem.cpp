#include "SoundSystem.h"
#include "ResourceManager.h"
#include <SDL_mixer.h>
#include <iostream>

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
	Mix_CloseAudio();
}

void amu::SDLSoundSystem::Update()
{
	while (not m_ShouldQuit)
	{
		m_SoundFuture.wait();
		
		std::lock_guard lockPlaying{ m_SoundMutex };

		while (not m_SoundRequestDeque.empty())
		{
			auto [id, volume] = m_SoundRequestDeque.front();
			PlaySoundEffect(id, volume);
			m_SoundRequestDeque.pop_front();
		}

		m_SoundPromise = std::promise<void>();
		m_SoundFuture = m_SoundPromise.get_future();
		m_IsScheduled = false;
	}
}

bool amu::SDLSoundSystem::RequestSoundEffect(int id, int volume)
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

	m_SoundRequestDeque.emplace_back(SoundRequest{ id, volume });

	if (not m_IsScheduled)
	{
		m_SoundPromise.set_value();
		m_IsScheduled = true;
	}

	return true;
}

void amu::SDLSoundSystem::AddSoundEffect(int id, const std::string& filePath)
{
	std::lock_guard lockMap{ m_SoundMutex };

	if (not m_SoundMap.contains(id))
	{
		m_SoundMap[id] = ResourceManager::GetInstance().LoadSoundEffect(filePath);
	}
}

void amu::SDLSoundSystem::SignalEnd()
{
	m_ShouldQuit = true;
	if (not m_IsScheduled)
	{
		m_SoundPromise.set_value();
		m_IsScheduled = true;
	}
}

void amu::SDLSoundSystem::PlaySoundEffect(int id, int volume)
{
	if (m_SoundMap.contains(id))
	{
		m_SoundMap[id]->PlaySoundEffect(volume);
	}
}

//////////////////////////////
/////////LOG SOUND SYSTEM
//////////////////////////////

amu::LogSoundSystem::LogSoundSystem(std::unique_ptr<SoundSystem>&& actualSoundSystemUPtr)
	: m_ActualSoundSystemUPtr{ std::move(actualSoundSystemUPtr) }
{
}

void amu::LogSoundSystem::Update()
{
	m_ActualSoundSystemUPtr->Update();
}

bool amu::LogSoundSystem::RequestSoundEffect(int id, int volume)
{
	if (m_ActualSoundSystemUPtr->RequestSoundEffect(id, volume))
	{
		std::cout << "Requested sound id: " << id << " at volume " << volume << "\n";
		return true;
	}
	std::cout << "Requested sound id: " << id << " but already existed\n";
	return false;
}

void amu::LogSoundSystem::AddSoundEffect(int id, const std::string& filePath)
{
	m_ActualSoundSystemUPtr->AddSoundEffect(id, filePath);
	std::cout << "Sound added with id: " << id << " from dir " << filePath << "\n";
}

void amu::LogSoundSystem::SignalEnd()
{
	m_ActualSoundSystemUPtr->SignalEnd();
	std::cout << "Sound execution should end\n";
}