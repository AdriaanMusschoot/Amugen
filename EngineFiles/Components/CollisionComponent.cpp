#include "CollisionComponent.h"
#include "SceneManager.h"
#include <iostream>

amu::CollisionComponent::CollisionComponent(GameObject* ownerObjectPtr, std::string_view const& tag)
	: Component(ownerObjectPtr)
	, m_OtherOverlapTag{ tag }
{
	GetComponentOwner()->AddComponent<DistanceComponent>(GetComponentOwner());
	m_DistanceComponentPtr = GetComponentOwner()->GetComponent<DistanceComponent>();

	m_TransformPtr = GetComponentOwner()->GetComponent<TransformComponent>();
}
