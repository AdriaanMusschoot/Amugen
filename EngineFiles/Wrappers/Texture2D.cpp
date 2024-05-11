#include <SDL.h>
#include "Texture2D.h"

pacman::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_TexturePtr);
}

glm::ivec2 pacman::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return glm::vec2{ dst.w,dst.h };
}

SDL_Texture* pacman::Texture2D::GetSDLTexture() const
{
	return m_TexturePtr;
}

pacman::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_TexturePtr = texture;
}
