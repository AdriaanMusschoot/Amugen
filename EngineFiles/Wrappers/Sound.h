#ifndef AMU_SOUND_WRAPPER_H
#define AMU_SOUND_WRAPPER_H

#include <string>

struct Mix_Chunk;

namespace amu
{

	class SoundEffect final
	{
	public:
		explicit SoundEffect(std::string_view const& fullPath);
		~SoundEffect();

		SoundEffect(SoundEffect const&) = delete;
		SoundEffect(SoundEffect&&) = delete;
		SoundEffect& operator= (SoundEffect const&) = delete;
		SoundEffect& operator= (SoundEffect&&) = delete;

		void PlaySoundEffect(int volume, int loops);
		void StopSoundEffect();
	private:
		std::string const m_FilePath{};
		//we still expose this type to whoever includes servicelocator who includes sound system which includes this 
		Mix_Chunk* m_SoundEffectPtr{};
		int m_Channel{};
	};

}

#endif