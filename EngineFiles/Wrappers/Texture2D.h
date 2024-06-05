#ifndef AMU_TEXTURE2D_WRAPPER_H
#define AMU_TEXTURE2D_WRAPPER_H

#include <glm/vec2.hpp>
#include "SDL2/include/SDL_rect.h"

struct SDL_Texture;

namespace amu
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
		SDL_Rect const& GetSourceRectangle() const;
		void SetSourceRectangle(SDL_Rect const& newSourceRect);

		Texture2D(Texture2D const&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (Texture2D const&) = delete;
		Texture2D& operator= (Texture2D&&) = delete;
	private:
		SDL_Texture* m_TexturePtr = nullptr;
		SDL_Rect m_SourceRect{ 0, 0, 0, 0 };
	};

}

#endif //AMU_TEXTURE2D_WRAPPER_H