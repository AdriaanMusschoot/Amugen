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
		virtual ~ServiceLocator() = default;

		ServiceLocator(ServiceLocator const&) = delete;
		ServiceLocator(ServiceLocator&&) = delete;
		ServiceLocator& operator=(ServiceLocator const&) = delete;
		ServiceLocator& operator=(ServiceLocator&&) = delete;

		ISoundSystem* GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<ISoundSystem>&& soundSystemUPtr);
	private:
		friend class Singleton<ServiceLocator>;

		explicit ServiceLocator() = default;

		static std::unique_ptr<ISoundSystem> m_SoundSystemUPtr;
	};

}

#endif //AMU_SERVICE_LOCATOR
