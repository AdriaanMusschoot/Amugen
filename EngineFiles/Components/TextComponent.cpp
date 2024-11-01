#include "TextComponent.h"
#include "TextComponent.h"
#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>

#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

amu::TextComponent::TextComponent(GameObject * ownerObjectPtr, std::string_view const& textToDisplay, std::string_view const& fontPath, unsigned int size)
	: Component(ownerObjectPtr)
	, m_Text{ textToDisplay }
	, m_FontUPtr{ amu::ResourceManager::GetInstance().LoadFont(fontPath, size) }
	, m_TransformPtr{ GetComponentOwner()->GetComponent<TransformComponent>() }
{
	GetComponentOwner()->AddComponent<RenderComponent>(GetComponentOwner());
	m_TextureComponentPtr = GetComponentOwner()->GetComponent<RenderComponent>();
	CreateTexture();
	m_NeedsUpdate = false;
}

void amu::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		CreateTexture();
		m_NeedsUpdate = false;
	}
}

void amu::TextComponent::Render() const
{
	m_TextureComponentPtr->Render();
}

glm::ivec2 amu::TextComponent::GetSize() const
{
	return m_TextureComponentPtr->GetSize();
}

void amu::TextComponent::SetText(std::string_view const& textToDisplay)
{
	m_Text = textToDisplay;
	m_NeedsUpdate = true;
}

void amu::TextComponent::CreateTexture()
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_FontUPtr->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(amu::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextureComponentPtr->SetTexture(std::make_unique<Texture2D>(texture));
	m_TextureComponentPtr->SetSourceRectangle(SDL_Rect{ 0, 0, m_TextureComponentPtr->GetSize().x, m_TextureComponentPtr->GetSize().y });
}
