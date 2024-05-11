#ifndef AMU_TEXTURE2D_WRAPPER_H
#define AMU_TEXTURE2D_WRAPPER_H

#include <glm/vec2.hpp>

struct SDL_Texture;
namespace pacman
{

	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_TexturePtr = nullptr;
	};

}

#endif //AMU_TEXTURE2D_WRAPPER_H