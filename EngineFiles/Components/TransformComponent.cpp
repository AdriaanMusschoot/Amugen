#include "GameObject.h"
#include "TransformComponent.h"

pacman::TransformComponent::TransformComponent(GameObject* ownerObjectPtr, const glm::vec2& pos)
	: Component(ownerObjectPtr)
	, m_LocalPosition{ pos }
	, m_WorldPosition{ pos }
    , m_TransformDirty{ false }
{
}

const glm::vec2& pacman::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

void pacman::TransformComponent::SetLocalPosition(const glm::vec2& newPosition)
{
	m_LocalPosition = newPosition;

    SetTransformDirty();
}

const glm::vec2& pacman::TransformComponent::GetWorldPosition() const
{
    if (m_TransformDirty)
    {
        const_cast<TransformComponent*>(this)->UpdateWorldPosition();
    }
	return m_WorldPosition;
}

void pacman::TransformComponent::Translate(const glm::vec2& offset)
{
    SetLocalPosition(GetLocalPosition() + offset);
}

void pacman::TransformComponent::UpdateWorldPosition()
{
	if (const GameObject* parentPtr = GetComponentOwner()->GetParent(); parentPtr == nullptr)
    {
        m_WorldPosition = m_LocalPosition;
    }
    else
    {
        m_WorldPosition = parentPtr->GetComponent<TransformComponent>()->GetWorldPosition() + m_LocalPosition;
    }
    m_TransformDirty = true;
}

void pacman::TransformComponent::SetTransformDirty()
{
    m_TransformDirty = true;
    const GameObject* ownerPtr = GetComponentOwner();

    for(size_t idx{}; idx < ownerPtr->GetChildCount(); ++idx)
    {
        ownerPtr->GetChildAt(static_cast<unsigned int>(idx))->GetComponent<TransformComponent>()->SetTransformDirty();
    }
}
