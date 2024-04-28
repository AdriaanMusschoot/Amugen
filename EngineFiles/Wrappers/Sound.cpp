#include "Sound.h"
#include "SDL_mixer.h"
#include <stdexcept>

amu::SoundEffect::SoundEffect(const std::string& fullPath)
{
	m_SoundEffectPtr = Mix_LoadWAV(fullPath.c_str());
	if (not m_SoundEffectPtr)
	{
		throw std::runtime_error(std::string("Failed to load sound effect: ") + SDL_GetError());
	}
}

void amu::SoundEffect::PlaySoundEffect(int volume)
{
	Mix_VolumeChunk(m_SoundEffectPtr, volume);

	Mix_PlayChannel(-1, m_SoundEffectPtr, 0);
}

amu::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_SoundEffectPtr);
}
