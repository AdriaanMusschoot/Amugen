#ifndef AMU_SOUND_SYSTEM_H
#define AMU_SOUND_SYSTEM_H

#include <memory>
#include <map>
#include <string>
#include <filesystem>
#include "Sound.h"
#include <deque>
#include <mutex>
#include <future>

namespace pacman
{
	using SoundId = int;
	class ISoundSystem //interface
	{
	public:
		virtual ~ISoundSystem() = default;

		virtual bool RequestSoundEffect(SoundId id, std::string_view const& filePath, int volume) = 0;
		virtual void SignalStart() = 0;
		virtual void SignalEnd() = 0;
	private:
	};

	class NullSoundSystem final : public ISoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override = default;

		NullSoundSystem(const NullSoundSystem&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&) = delete;
		NullSoundSystem(NullSoundSystem&&) = delete;
		NullSoundSystem& operator= (const NullSoundSystem&&) = delete;

		bool RequestSoundEffect(SoundId, std::string_view const&, int) override { return false; };
		void SignalStart() override {};
		void SignalEnd() override {};
	private:
	};

	class SDLSoundSystem final : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;

		void Update();
		bool RequestSoundEffect(SoundId id, std::string_view const& filePath, int volume) override;
		void SignalStart() override;
		void SignalEnd() override;
	private:
		struct SoundRequest 
		{
			int ID;
			std::string_view FilePath;
			int Volume;
		};

		std::map<int, std::unique_ptr<SoundEffect>> m_SoundMap{};
		std::deque<SoundRequest> m_SoundRequestDeque{};

		std::thread m_SoundThread{};
		std::mutex m_SoundMutex{};
		std::promise<void> m_SoundPromise{};
		std::future<void> m_SoundFuture{};

		bool m_ShouldQuit{};

		bool m_IsScheduled{};

		void PlaySoundEffect(SoundId id, std::string_view const& fileName, int volume);
	};

	class LogSoundSystem final : public ISoundSystem
	{
	public:
		LogSoundSystem(std::unique_ptr<ISoundSystem>&& actualSoundSystemUPtr);
		~LogSoundSystem() override = default;

		LogSoundSystem(const LogSoundSystem&) = delete;
		LogSoundSystem& operator= (const LogSoundSystem&) = delete;
		LogSoundSystem(LogSoundSystem&&) = delete;
		LogSoundSystem& operator= (const LogSoundSystem&&) = delete;

		bool RequestSoundEffect(SoundId id, std::string_view const& filePath, int volume) override;
		void SignalStart() override;
		void SignalEnd() override;
	private:
		std::unique_ptr<ISoundSystem> m_ActualSoundSystemUPtr{};
	};

}
#endif //AMU_SOUND_SYSTEM_H