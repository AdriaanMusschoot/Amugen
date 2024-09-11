#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "RenderComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace amu
{

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(GameObject * ownerObjectPtr, std::string_view const& textToDisplay, std::string_view const& fontPath, unsigned int size = 10);
		virtual ~TextComponent() override = default;
	
		TextComponent(TextComponent const&) = delete;
		TextComponent(TextComponent&&) = delete;
		TextComponent& operator= (TextComponent const&) = delete;
		TextComponent& operator= (TextComponent&&) = delete;
	
		void Update() override;
		void Render() const override;
		
		glm::ivec2 GetSize() const;

		void SetText(std::string_view const& textToDisplay);
	private:

		std::string m_Text{ "" };

		std::unique_ptr<amu::Font> m_FontUPtr{ nullptr };

		TransformComponent* m_TransformPtr{ nullptr };

		RenderComponent* m_TextureComponentPtr{ nullptr };

		bool m_NeedsUpdate{ true };

		void CreateTexture();
	};

}