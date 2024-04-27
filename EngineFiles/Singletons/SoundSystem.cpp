#include "SoundSystem.h"
#include "ResourceManager.h"
#include <SDL_mixer.h>

amu::SDLSoundSystem::SDLSoundSystem()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

amu::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_CloseAudio();
}

void amu::SDLSoundSystem::PlaySoundEffect(SoundID id, int volume)
{
	if (m_SoundMap.contains(id))
	{
		Mix_VolumeChunk(m_SoundMap[id]->GetSoundEffect(), volume);

		Mix_PlayChannel(-1, m_SoundMap[id]->GetSoundEffect(), 0);
	}
}

void amu::SDLSoundSystem::AddSound(SoundID id, const std::string& filePath)
{
	if (not m_SoundMap.contains(id))
	{
		m_SoundMap[id] = ResourceManager::GetInstance().LoadSoundEffect(filePath);
	}
}
