#ifndef PM_DISTANCE_COMPONENT_H
#define PM_DISTANCE_COMPONENT_H
#include "Component.h"
#include <glm/glm.hpp>

namespace amu
{

	class DistanceComponent final : public Component
	{
	public:
		DistanceComponent(GameObject* ownerObjectPtr);
		virtual ~DistanceComponent() override = default;

		DistanceComponent(DistanceComponent const&) = delete;
		DistanceComponent(DistanceComponent&&) = delete;
		DistanceComponent& operator=(DistanceComponent const&) = delete;
		DistanceComponent& operator=(DistanceComponent&&) = delete;

		bool Check(glm::vec2 const& center1, glm::vec2 const& center2, std::float_t const& distance);
	private:
	};

}

#endif //PM_DISTANCE_COMPONENT_H