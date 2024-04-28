#ifndef AMU_SOUND_WRAPPER_H
#define AMU_SOUND_WRAPPER_H
#include <string>

struct Mix_Chunk;

namespace amu
{

	class SoundEffect final
	{
	public:
		explicit SoundEffect(const std::string& fullPath);
		void PlaySoundEffect(int volume);
		~SoundEffect();

		SoundEffect(const SoundEffect&) = delete;
		SoundEffect(SoundEffect&&) = delete;
		SoundEffect& operator= (const SoundEffect&) = delete;
		SoundEffect& operator= (const SoundEffect&&) = delete;
	private:
		Mix_Chunk* m_SoundEffectPtr = nullptr;
	};

}

#endif