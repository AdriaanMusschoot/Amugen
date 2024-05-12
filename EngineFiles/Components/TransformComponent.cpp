#include "GameObject.h"
#include "TransformComponent.h"

amu::TransformComponent::TransformComponent(GameObject* ownerObjectPtr, glm::vec2 const& pos)
	: Component(ownerObjectPtr)
	, m_LocalPosition{ pos }
	, m_WorldPosition{ pos }
    , m_TransformDirty{ false }
{
}

const glm::vec2& amu::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

void amu::TransformComponent::SetLocalPosition(glm::vec2 const& newPosition)
{
	m_LocalPosition = newPosition;

    SetTransformDirty();
}

const glm::vec2& amu::TransformComponent::GetWorldPosition() const
{
    if (m_TransformDirty)
    {
        const_cast<TransformComponent*>(this)->UpdateWorldPosition();
    }
	return m_WorldPosition;
}

void amu::TransformComponent::Translate(glm::vec2 const& offset)
{
    SetLocalPosition(GetLocalPosition() + offset);
}

void amu::TransformComponent::UpdateWorldPosition()
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

void amu::TransformComponent::SetTransformDirty()
{
    m_TransformDirty = true;
    const GameObject* ownerPtr = GetComponentOwner();

    for(std::int64_t idx{}; idx < ownerPtr->GetChildCount(); ++idx)
    {
        ownerPtr->GetChildAt(idx)->GetComponent<TransformComponent>()->SetTransformDirty();
    }
}
