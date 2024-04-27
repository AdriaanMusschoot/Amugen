#include "ServiceLocator.h"
#include "SoundSystem.h"

std::unique_ptr<amu::SoundSystem> amu::ServiceLocator::m_SoundSystemUPtr{ std::make_unique<NullSoundSystem>() };

amu::SoundSystem* amu::ServiceLocator::GetSoundSystem()
{
	return m_SoundSystemUPtr.get();
}

void amu::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystemUPtr)
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
