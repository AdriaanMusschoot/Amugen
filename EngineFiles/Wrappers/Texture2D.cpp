#include "Texture2D.h"
#include <SDL.h>
#include "Texture2D.h"

amu::Texture2D::Texture2D(SDL_Texture* texture)
	: m_SourceRect{ SDL_Rect{ 0, 0, 0, 0 }}
{
	m_TexturePtr = texture;
}

amu::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_TexturePtr);
}

glm::ivec2 amu::Texture2D::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return glm::vec2{ dst.w,dst.h };
}

SDL_Texture* amu::Texture2D::GetSDLTexture() const
{
	return m_TexturePtr;
}


SDL_Rect const& amu::Texture2D::GetSourceRectangle() const
{
	return m_SourceRect;
}

void amu::Texture2D::SetSourceRectangle(SDL_Rect const& newSourceRect)
{
	m_SourceRect = newSourceRect;
}
