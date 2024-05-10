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
		void PlaySoundEffect(int volume);
		~SoundEffect();

		SoundEffect(const SoundEffect&) = delete;
		SoundEffect(SoundEffect&&) = delete;
		SoundEffect& operator= (const SoundEffect&) = delete;
		SoundEffect& operator= (const SoundEffect&&) = delete;
	private:
		std::string const m_FilePath{};
		//we still expose this type to whoever includes servicelocator who includes sound system which includes this 
		Mix_Chunk* m_SoundEffectPtr{};
	};

}

#endif