#ifndef AMU_SOUND_SYSTEM_H
#define AMU_SOUND_SYSTEM_H
#include <memory>
#include <map>
#include <string>
#include <filesystem>
#include "Sound.h"
#include <deque>

namespace amu
{
	class SoundSystem //interface
	{
	public:
		virtual ~SoundSystem() = default;

		virtual void Update() = 0;
		virtual bool RequestSoundEffect(int id, int volume) = 0;
		virtual void AddSoundEffect(int id, const std::string& filePath) = 0;
		virtual void PlaySoundEffect(int id, int volume) = 0;
	private:
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override = default;

		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&&) = delete;

		void Update() override {};
		bool RequestSoundEffect(int, int) override { return false; };
		void AddSoundEffect(int, const std::string&) override {};
	private:
		void PlaySoundEffect(int, int) override {};
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;

		void Update() override;
		bool RequestSoundEffect(int id, int volume) override;
		virtual void AddSoundEffect(int id, const std::string& filePath) override;
	private:
		struct SoundRequest 
		{
			int ID;
			int Volume;
		};

		std::map<int, std::unique_ptr<SoundEffect>> m_SoundMap{};
		std::deque<SoundRequest> m_SoundRequestDeque{};

		void PlaySoundEffect(int id, int volume) override;
	};

	class LogSoundSystem final : public SoundSystem
	{
	public:
		LogSoundSystem(std::unique_ptr<SoundSystem>&& actualSoundSystemUPtr);
		~LogSoundSystem() override = default;

		LogSoundSystem(const LogSoundSystem&) = delete;
		LogSoundSystem& operator= (const LogSoundSystem&) = delete;
		LogSoundSystem(LogSoundSystem&&) = delete;
		LogSoundSystem& operator= (const LogSoundSystem&&) = delete;

		void Update() override;
		bool RequestSoundEffect(int id, int volume) override;
		virtual void AddSoundEffect(int id, const std::string& filePath) override;

	private:
		void PlaySoundEffect(int id, int volume);
		std::unique_ptr<SoundSystem> m_ActualSoundSystemUPtr{};
	};

}
#endif //AMU_SOUND_SYSTEM_H