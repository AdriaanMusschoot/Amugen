#include "Sound.h"
#include "Sound.h"
#include "SDL_mixer.h"
#include <stdexcept>

amu::SoundEffect::SoundEffect(std::string_view const& fullPath)
	: m_FilePath{ fullPath }
{

}

void amu::SoundEffect::PlaySoundEffect(int volume, int loops)
{
	if (not m_SoundEffectPtr)
	{
		m_SoundEffectPtr = Mix_LoadWAV(m_FilePath.data());
	}

	Mix_VolumeChunk(m_SoundEffectPtr, volume);

	m_Channel = Mix_PlayChannel(-1, m_SoundEffectPtr, loops);
}

void amu::SoundEffect::StopSoundEffect()
{
	Mix_HaltChannel(m_Channel);
}

amu::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_SoundEffectPtr);
}