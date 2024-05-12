#ifndef AMU_COLLISION_COMPONENT_H
#define AMU_COLLISION_COMPONENT_H
#include "Component.h"
#include "DistanceComponent.h"
#include "TransformComponent.h"
#include "Subject.h"
#include <string>

namespace amu
{

	class CollisionComponent final : public Component, public Subject
	{
	public:
		explicit CollisionComponent(GameObject* ownerObjectPtr, std::string_view const& tag, Event type);
		virtual ~CollisionComponent() override = default;

		CollisionComponent(CollisionComponent const&) = delete;
		CollisionComponent(CollisionComponent&&) = delete;
		CollisionComponent& operator= (CollisionComponent const&) = delete;
		CollisionComponent& operator= (CollisionComponent&&) = delete;

		void Update() override;
	private:
		std::string const m_OtherOverlapTag{ "" };
		Event m_CollisionEvent{ -1 };
		DistanceComponent* m_DistanceComponentPtr{ nullptr };
		TransformComponent* m_TransformPtr{ nullptr };
	};

}

#endif //AMU_COLLISION_COMPONENT_H