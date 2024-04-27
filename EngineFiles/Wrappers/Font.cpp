#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* amu::Font::GetFont() const
{
	return m_FontPtr;
}

amu::Font::Font(const std::string& fullPath, unsigned int size) : m_FontPtr(nullptr)
{
	m_FontPtr = TTF_OpenFont(fullPath.c_str(), size);
	if (not m_FontPtr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

amu::Font::~Font()
{
	TTF_CloseFont(m_FontPtr);
}
