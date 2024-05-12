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
		amu::Renderer::GetInstance().RenderTexture(*m_TextureUPtr, m_TransformPtr->GetWorldPosition().x, m_TransformPtr->GetWorldPosition().y);
	}
}

glm::vec2 amu::RenderComponent::GetSize() const
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