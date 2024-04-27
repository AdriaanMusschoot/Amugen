#ifndef AMU_SERVICE_LOCATOR
#define AMU_SERVICE_LOCATOR
#include <memory>
#include <Singleton.h>
#include "SoundSystem.h"

namespace amu
{

	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		SoundSystem* GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& soundSystemUPtr);
	private:
		friend class Singleton<ServiceLocator>;

		static std::unique_ptr<SoundSystem> m_SoundSystemUPtr;
	};

}

#endif //AMU_SERVICE_LOCATOR
