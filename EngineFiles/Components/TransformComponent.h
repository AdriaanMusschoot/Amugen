#pragma once
#include <glm/glm.hpp>

#include "Component.h"

namespace amu
{
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject * ownerObjectPtr, glm::vec2 const& pos);
		virtual ~TransformComponent() override = default;

		TransformComponent(TransformComponent const&) = delete;
		TransformComponent(TransformComponent&&) = delete;
		TransformComponent& operator= (TransformComponent const&) = delete;
		TransformComponent& operator= (TransformComponent&&) = delete;

		const glm::vec2& GetLocalPosition() const;
		void SetLocalPosition(glm::vec2 const& newPosition);

		const glm::vec2& GetWorldPosition() const;
		void Translate(glm::vec2 const& offset);

		void SetTransformDirty();
	private:
		glm::vec2 m_LocalPosition{ 0, 0 };
		glm::vec2 m_WorldPosition{ 0, 0 };

		bool m_TransformDirty{ false };

		void UpdateWorldPosition();
	};
}