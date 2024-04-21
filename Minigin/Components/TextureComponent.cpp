#include "Components/TextureComponent.h"

#include "SDL_egl.h"
#include "Singletons/Renderer.h"
#include "Singletons/ResourceManager.h"
#include "Base/GameObject.h"

amu::RenderComponent::RenderComponent(GameObject* ownerObjectPtr, const std::string& fileName)
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

void amu::RenderComponent::SetTexture(const std::string& fileName)
{
	m_TextureUPtr = amu::ResourceManager::GetInstance().LoadTexture(fileName);
}

void amu::RenderComponent::SetTexture(std::unique_ptr<Texture2D> textureUPtr)
{
	m_TextureUPtr = std::move(textureUPtr);
}