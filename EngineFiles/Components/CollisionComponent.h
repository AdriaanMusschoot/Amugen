#ifndef AMU_COLLISION_COMPONENT_H
#define AMU_COLLISION_COMPONENT_H
#include "Component.h"
#include "DistanceComponent.h"
#include "TransformComponent.h"
#include "Subject.h"
#include <string>

namespace amu
{

	class CollisionComponent : public Component
	{
	public:
		explicit CollisionComponent(GameObject* ownerObjectPtr, std::string_view const& tag);
		virtual ~CollisionComponent() override = default;

		CollisionComponent(CollisionComponent const&) = delete;
		CollisionComponent(CollisionComponent&&) = delete;
		CollisionComponent& operator= (CollisionComponent const&) = delete;
		CollisionComponent& operator= (CollisionComponent&&) = delete;

		virtual void OnCollision(amu::CollisionComponent* otherCollider) = 0;
	private:
		std::string const m_OtherOverlapTag{ "" };
		DistanceComponent* m_DistanceComponentPtr{ nullptr };
		TransformComponent* m_TransformPtr{ nullptr };
	};

}

#endif //AMU_COLLISION_COMPONENT_H