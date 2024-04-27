#ifndef AMU_SOUND_WRAPPER_H
#define AMU_SOUND_WRAPPER_H
#include <string>

struct Mix_Chunk;

namespace amu
{

	class SoundEffect final
	{
	public:
		Mix_Chunk* GetSoundEffect() const;
		explicit SoundEffect(const std::string& fullPath);
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