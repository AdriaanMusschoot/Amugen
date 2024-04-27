#ifndef AMU_SOUND_SYSTEM_H
#define AMU_SOUND_SYSTEM_H
#include <memory>
#include <map>
#include <string>
#include <filesystem>
#include "Sound.h"

namespace amu
{
	class SoundSystem //interface
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void PlaySoundEffect(int id, int volume) = 0;
		virtual void AddSound(int id, const std::string& filePath) = 0;
	private:
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		~NullSoundSystem() override = default;

		void PlaySoundEffect(int, int) override{};
		void AddSound(int, const std::string&) override{};
	private:
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		void PlaySoundEffect(int id, int volume) override;
		virtual void AddSound(int id, const std::string& filePath) override;
	private:
		std::map<int, std::unique_ptr<SoundEffect>> m_SoundMap;
	};

}
#endif //AMU_SOUND_SYSTEM_H