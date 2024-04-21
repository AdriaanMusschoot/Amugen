#pragma once

#pragma once
#include "Base/Component.h"
#include "Base/GameObject.h"
#include "Base/Subject.h"

namespace amu
{

	class ScoreComponent final : public Component, public Subject
	{
	public:
		explicit ScoreComponent(GameObject* ownerObjectPtr, int score = 0);
		virtual ~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent&) = delete;
		ScoreComponent& operator= (const ScoreComponent&) = delete;
		ScoreComponent(ScoreComponent&&) = delete;
		ScoreComponent& operator= (const ScoreComponent&&) = delete;

		void IncreaseScore(int value);

		int GetScore() const;

	private:
		int m_CurrentScore{ 0 };

	};

}