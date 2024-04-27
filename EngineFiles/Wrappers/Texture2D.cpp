#include <SDL.h>
#include "Texture2D.h"

amu::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_TexturePtr);
}

glm::ivec2 amu::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* amu::Texture2D::GetSDLTexture() const
{
	return m_TexturePtr;
}

amu::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_TexturePtr = texture;
}
