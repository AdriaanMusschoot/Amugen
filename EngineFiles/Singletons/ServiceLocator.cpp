#include "ServiceLocator.h"
#include "SoundSystem.h"

std::unique_ptr<amu::ISoundSystem> amu::ServiceLocator::m_SoundSystemUPtr{ std::make_unique<NullSoundSystem>() };

amu::ISoundSystem* amu::ServiceLocator::GetSoundSystem()
{
	return m_SoundSystemUPtr.get();
}

void amu::ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystemUPtr)
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
