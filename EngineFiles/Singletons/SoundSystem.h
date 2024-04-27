#ifndef AMU_SOUND_SYSTEM_H
#define AMU_SOUND_SYSTEM_H
#include <memory>
#include <map>
#include <string>
#include <filesystem>
#include "Sound.h"

namespace amu
{
	enum class SoundID
	{
		PacmanDeath
	};

	class SoundSystem //interface
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void PlaySoundEffect(SoundID id, int volume) = 0;
		virtual void AddSound(SoundID id, const std::string& filePath) = 0;
	private:
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		~NullSoundSystem() override = default;

		void PlaySoundEffect(SoundID, int) override{};
		virtual void AddSound(SoundID, const std::string&) override{};
	private:
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		void PlaySoundEffect(SoundID id, int volume) override;
		virtual void AddSound(SoundID id, const std::string& filePath) override;
	private:
		std::map<SoundID, std::unique_ptr<SoundEffect>> m_SoundMap;
	};

}
#endif //AMU_SOUND_SYSTEM_H