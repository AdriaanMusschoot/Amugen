#include "ServiceLocator.h"
#include "SoundSystem.h"

std::unique_ptr<pacman::ISoundSystem> pacman::ServiceLocator::m_SoundSystemUPtr{ std::make_unique<NullSoundSystem>() };

pacman::ISoundSystem* pacman::ServiceLocator::GetSoundSystem()
{
	return m_SoundSystemUPtr.get();
}

void pacman::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystemUPtr)
{
	if (soundSystemUPtr)
	{
		m_SoundSystemUPtr = std::move(soundSystemUPtr);
	}
	else
	{
		m_SoundSystemUPtr = std::make_unique<NullSoundSystem>();
	}
}
