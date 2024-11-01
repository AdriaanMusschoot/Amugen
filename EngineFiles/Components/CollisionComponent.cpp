#include <execution>
#include <iostream>

#include "CollisionComponent.h"
#include "DistanceComponent.h"
#include "GameObject.h"

amu::CollisionComponent::CollisionComponent(GameObject* ownerObjectPtr, std::vector<std::string> const& tagVec)
	: Component(ownerObjectPtr)
	, m_OtherTagVec{ tagVec }
{
	GetComponentOwner()->AddComponent<DistanceComponent>(GetComponentOwner());
	m_DistanceComponentPtr = GetComponentOwner()->GetComponent<DistanceComponent>();
}

size_t amu::CollisionComponent::NumberOfTags()
{
	return std::size(m_OtherTagVec);
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
