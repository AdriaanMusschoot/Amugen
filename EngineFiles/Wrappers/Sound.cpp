#include "Sound.h"
#include "SDL_mixer.h"
#include <stdexcept>

amu::SoundEffect::SoundEffect(std::string_view const& fullPath)
	: m_FilePath{ fullPath }
{

}

void amu::SoundEffect::PlaySoundEffect(int volume)
{
	if (not m_SoundEffectPtr)
	{
		m_SoundEffectPtr = Mix_LoadWAV(m_FilePath.data());
	}

	Mix_VolumeChunk(m_SoundEffectPtr, volume);

	Mix_PlayChannel(-1, m_SoundEffectPtr, 0);
}

amu::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_SoundEffectPtr);
}