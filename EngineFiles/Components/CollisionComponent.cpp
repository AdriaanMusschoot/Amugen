#include "CollisionComponent.h"
#include "SceneManager.h"
#include <iostream>

amu::CollisionComponent::CollisionComponent(GameObject* ownerObjectPtr, std::string_view const& tag, Event type)
	: Component(ownerObjectPtr)
	, Subject(ownerObjectPtr)
	, m_OtherOverlapTag{ tag }
	, m_CollisionEvent{ type }
{
	GetComponentOwner()->AddComponent<DistanceComponent>(GetComponentOwner());
	m_DistanceComponentPtr = GetComponentOwner()->GetComponent<DistanceComponent>();

	m_TransformPtr = GetComponentOwner()->GetComponent<TransformComponent>();
}

void amu::CollisionComponent::Update()
{
	auto objectVec = amu::SceneManager::GetInstance().GetCurrentScene()->GetObjectsOfType(m_OtherOverlapTag);
	for (auto& object : objectVec)
	{
		bool overlapping = m_DistanceComponentPtr->Check(m_TransformPtr->GetWorldPosition(), object->GetComponent<TransformComponent>()->GetWorldPosition(), 1);
		if (overlapping)
		{
			NotifyObservers(m_CollisionEvent);
		}
	}
}
