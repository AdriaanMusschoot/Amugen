#ifndef AMU_RESOURCE_MANAGER_H
#define AMU_RESOURCE_MANAGER_H

#include <filesystem>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Sound.h"

namespace amu
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		virtual ~ResourceManager() = default;

		ResourceManager(ResourceManager const&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(ResourceManager const&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		void Init(const std::filesystem::path& data);
		std::unique_ptr<Texture2D> LoadTexture(const std::string_view& file) const;
		std::unique_ptr<Font> LoadFont(const std::string_view& file, unsigned int size) const;
		std::unique_ptr<SoundEffect> LoadSoundEffect(const std::string_view& file) const;
	private:
		friend class Singleton<ResourceManager>;
		explicit ResourceManager() = default;
		std::filesystem::path m_DataPath = "";
	};
}

#endif AMU_RESOURCE_MANAGER_H