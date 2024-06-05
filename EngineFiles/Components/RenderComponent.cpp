#include "RenderComponent.h"
#include "RenderComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

amu::RenderComponent::RenderComponent(GameObject* ownerObjectPtr, std::string_view const& fileName)
	: Component(ownerObjectPtr)
	, m_TransformPtr{ GetComponentOwner()->GetComponent<TransformComponent>() }
{
	if (fileName != "")
	{
		SetTexture(fileName);
	}
}

void amu::RenderComponent::Render() const
{
	if (m_TextureUPtr != nullptr)
	{
		amu::Renderer::GetInstance().RenderTexture(*m_TextureUPtr, m_TransformPtr->GetWorldPosition().x, m_TransformPtr->GetWorldPosition().y, m_TextureUPtr->GetSourceRectangle());
	}
}

glm::ivec2 amu::RenderComponent::GetSize() const
{
	return m_TextureUPtr->GetSize();
}

void amu::RenderComponent::SetTexture(std::string_view const& fileName)
{
	m_TextureUPtr = amu::ResourceManager::GetInstance().LoadTexture(fileName);
}

void amu::RenderComponent::SetTexture(std::unique_ptr<Texture2D> textureUPtr)
{
	m_TextureUPtr = std::move(textureUPtr);
}

void amu::RenderComponent::SetSourceRectangle(SDL_Rect const& sourceRect)
{
	m_TextureUPtr->SetSourceRectangle(sourceRect);
}

SDL_Rect const& amu::RenderComponent::GetSourceRectangle() const
{
	return m_TextureUPtr->GetSourceRectangle();
}