#include "SoundSystem.h"
#include "ResourceManager.h"
#include <SDL_mixer.h>
#include <iostream>

//////////////////////////////
/////////SDL SOUND SYSTEM
//////////////////////////////

amu::SDLSoundSystem::SDLSoundSystem()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

amu::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_CloseAudio();
}

void amu::SDLSoundSystem::Update()
{
	while (m_SoundRequestDeque.begin() != m_SoundRequestDeque.end())
	{
		auto [id, volume] = m_SoundRequestDeque.front();
		PlaySoundEffect(id, volume);
		m_SoundRequestDeque.pop_front();
	}
}

bool amu::SDLSoundSystem::RequestSoundEffect(int id, int volume)
{
	if (bool hasFoundSimilar = std::any_of(m_SoundRequestDeque.begin(), m_SoundRequestDeque.end(),
		[&](SoundRequest& req)
		{
			if (req.ID == id)
			{
				req.Volume = std::max(req.Volume, volume);
				return true;
			}
			return false;
		}); hasFoundSimilar == true)
	{
		return false;
	}

	m_SoundRequestDeque.emplace_back(SoundRequest{ id, volume });

	return true;
}

void amu::SDLSoundSystem::AddSoundEffect(int id, const std::string& filePath)
{
	if (not m_SoundMap.contains(id))
	{
		m_SoundMap[id] = ResourceManager::GetInstance().LoadSoundEffect(filePath);
	}
}

void amu::SDLSoundSystem::PlaySoundEffect(int id, int volume)
{
	if (m_SoundMap.contains(id))
	{
		Mix_VolumeChunk(m_SoundMap[id]->GetSoundEffect(), volume);

		Mix_PlayChannel(-1, m_SoundMap[id]->GetSoundEffect(), 0);
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
	return false;
}

void amu::LogSoundSystem::AddSoundEffect(int id, const std::string& filePath)
{
	m_ActualSoundSystemUPtr->AddSoundEffect(id, filePath);
	std::cout << "Sound added with id: " << id << " from dir " << filePath << "\n";
}

void amu::LogSoundSystem::PlaySoundEffect(int id, int volume)
{
	m_ActualSoundSystemUPtr->PlaySoundEffect(id, volume);
	std::cout << "Played sound id: " << id << "at volume " << volume << "\n";
}
