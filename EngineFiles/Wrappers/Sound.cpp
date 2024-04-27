#include "Sound.h"
#include "SDL_mixer.h"
#include <stdexcept>

Mix_Chunk* amu::SoundEffect::GetSoundEffect() const
{
	return m_SoundEffectPtr;
}

amu::SoundEffect::SoundEffect(const std::string& fullPath)
{
	m_SoundEffectPtr = Mix_LoadWAV(fullPath.c_str());
	if (not m_SoundEffectPtr)
	{
		throw std::runtime_error(std::string("Failed to load sound effect: ") + SDL_GetError());
	}
}

amu::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_SoundEffectPtr);
}
