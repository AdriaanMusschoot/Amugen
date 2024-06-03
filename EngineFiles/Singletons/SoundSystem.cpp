#include "SoundSystem.h"
#include "SoundSystem.h"
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
	Mix_AllocateChannels(100);
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

		std::deque<SoundRequest> soundDequeToPlay{};

		{
			std::lock_guard lock(m_SoundMutex);
			soundDequeToPlay = m_SoundRequestDeque;
			m_SoundRequestDeque.clear();

			m_SoundPromise = std::promise<void>();
			m_SoundFuture = m_SoundPromise.get_future();
			m_IsScheduled = false;
		}
	
		while (not soundDequeToPlay.empty())
		{
			auto [id, fileName, volume, loops] = soundDequeToPlay.front();
			PlaySoundEffect(id, fileName, volume, loops);
			soundDequeToPlay.pop_front();
		}
	}
}

bool amu::SDLSoundSystem::RequestSoundEffect(SoundId id, std::string_view const& filePath, int volume, int loops)
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

	m_SoundRequestDeque.emplace_back(SoundRequest{ id, filePath, volume, loops });

	if (not m_IsScheduled)
	{
		m_SoundPromise.set_value();
		m_IsScheduled = true;
	}

	return true;
}

bool amu::SDLSoundSystem::StopSoundEffect(SoundId id)
{
	if (not m_SoundMap.contains(id)) return false;

	m_SoundMap[id]->StopSoundEffect();

	return true;
}

void amu::SDLSoundSystem::SignalStart()
{
	std::lock_guard close{ m_SoundMutex };
	m_SoundThread = std::thread(&SDLSoundSystem::Update, this);
	m_SoundThread.detach();
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

void amu::SDLSoundSystem::PlaySoundEffect(SoundId id, std::string_view const& fileName, int volume, int loops)
{
	if (not m_SoundMap.contains(id))
	{
		m_SoundMap[id] = ResourceManager::GetInstance().LoadSoundEffect(fileName);
	}

	m_SoundMap[id]->PlaySoundEffect(volume, loops);
}

//////////////////////////////
/////////LOG SOUND SYSTEM
//////////////////////////////

amu::LogSoundSystem::LogSoundSystem(std::unique_ptr<ISoundSystem>&& actualSoundSystemUPtr)
	: m_ActualSoundSystemUPtr{ std::move(actualSoundSystemUPtr) }
{
}

bool amu::LogSoundSystem::RequestSoundEffect(SoundId id, std::string_view const& filePath, int volume, int loops)
{
	if (m_ActualSoundSystemUPtr->RequestSoundEffect(id, filePath, volume, loops))
	{
		std::cout << "Requested sound id: " << id << " from dir " << filePath << "\n";
		std::cout << "Requested sound id: " << id << " at volume " << volume << "\n";
		return true;
	}
	return false;
}

bool amu::LogSoundSystem::StopSoundEffect(SoundId id)
{
	if (m_ActualSoundSystemUPtr->StopSoundEffect(id))
	{
		std::cout << "Stop Sound Effect\n";
		return true;
	}
	return false;
}

void amu::LogSoundSystem::SignalStart()
{
	m_ActualSoundSystemUPtr->SignalStart();
	std::cout << "Sound execution should start\n";
}

void amu::LogSoundSystem::SignalEnd()
{
	m_ActualSoundSystemUPtr->SignalEnd();
	std::cout << "Sound execution should end\n";
}