#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

pacman::RenderComponent::RenderComponent(GameObject* ownerObjectPtr, std::string_view const& fileName)
	: Component(ownerObjectPtr)
	, m_TransformPtr{ GetComponentOwner()->GetComponent<TransformComponent>() }
{
	if (fileName != "")
	{
		SetTexture(fileName);
	}
}

void pacman::RenderComponent::Render() const
{
	if (m_TextureUPtr != nullptr)
	{
		pacman::Renderer::GetInstance().RenderTexture(*m_TextureUPtr, m_TransformPtr->GetWorldPosition().x, m_TransformPtr->GetWorldPosition().y);
	}
}

glm::ivec2 pacman::RenderComponent::GetSize() const
{
	return m_TextureUPtr->GetSize();
}

void pacman::RenderComponent::SetTexture(std::string_view const& fileName)
{
	m_TextureUPtr = pacman::ResourceManager::GetInstance().LoadTexture(fileName);
}

void pacman::RenderComponent::SetTexture(std::unique_ptr<Texture2D> textureUPtr)
{
	m_TextureUPtr = std::move(textureUPtr);
}