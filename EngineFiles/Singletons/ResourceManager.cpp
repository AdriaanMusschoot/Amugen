#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void amu::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_DataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::unique_ptr<amu::Texture2D> amu::ResourceManager::LoadTexture(const std::string_view& file) const
{
	const auto fullPath = m_DataPath/file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_unique<Texture2D>(texture);
}

std::unique_ptr<amu::Font> amu::ResourceManager::LoadFont(const std::string_view& file, unsigned int size) const
{
	const auto fullPath = m_DataPath/file;
	return std::make_unique<Font>(fullPath.string(), size);
}

std::unique_ptr<amu::SoundEffect> amu::ResourceManager::LoadSoundEffect(const std::string_view& file) const
{
	const auto fullPath = m_DataPath/file;
	return std::make_unique<SoundEffect>(fullPath.string());
}
