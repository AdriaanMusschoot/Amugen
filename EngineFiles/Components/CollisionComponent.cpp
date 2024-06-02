#include "CollisionComponent.h"
#include "SceneManager.h"
#include "execution"
#include <iostream>

amu::CollisionComponent::CollisionComponent(GameObject* ownerObjectPtr, std::vector<std::string> const& tagVec)
	: Component(ownerObjectPtr)
	, m_OtherTagVec{ tagVec }
{
	GetComponentOwner()->AddComponent<DistanceComponent>(GetComponentOwner());
	m_DistanceComponentPtr = GetComponentOwner()->GetComponent<DistanceComponent>();
}

bool amu::CollisionComponent::FindTag(std::string_view const& tagToFind)
{
	return std::any_of
	( 
		std::execution::par_unseq, 
		m_OtherTagVec.begin(), m_OtherTagVec.end(),
		[&](std::string const& tag)
		{
			return tag == tagToFind;
		}
	);
}
