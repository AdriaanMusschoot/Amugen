#ifndef AMU_COLLISION_COMPONENT_H
#define AMU_COLLISION_COMPONENT_H

#include "Component.h"
#include "DistanceComponent.h"
#include "TransformComponent.h"
#include <string>
#include <vector>

namespace amu
{

	class CollisionComponent : public Component
	{
	public:
		explicit CollisionComponent(GameObject* ownerObjectPtr, std::vector<std::string> const& tagVec);
		virtual ~CollisionComponent() override = default;

		CollisionComponent(CollisionComponent const&) = delete;
		CollisionComponent(CollisionComponent&&) = delete;
		CollisionComponent& operator= (CollisionComponent const&) = delete;
		CollisionComponent& operator= (CollisionComponent&&) = delete;

		bool FindTag(std::string_view const& tag);

		virtual void OnCollision(amu::CollisionComponent* otherCollider) = 0;
	private:
		std::vector<std::string> const m_OtherTagVec{ "" };
		DistanceComponent* m_DistanceComponentPtr{ nullptr };
	};

}

#endif //AMU_COLLISION_COMPONENT_H