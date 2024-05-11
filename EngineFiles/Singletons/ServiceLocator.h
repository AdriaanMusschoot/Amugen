#ifndef AMU_SERVICE_LOCATOR
#define AMU_SERVICE_LOCATOR
#include <memory>
#include <Singleton.h>
#include "SoundSystem.h"

namespace pacman
{

	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		ISoundSystem* GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystemUPtr);
	private:
		friend class Singleton<ServiceLocator>;

		static std::unique_ptr<ISoundSystem> m_SoundSystemUPtr;
	};

}

#endif //AMU_SERVICE_LOCATOR
