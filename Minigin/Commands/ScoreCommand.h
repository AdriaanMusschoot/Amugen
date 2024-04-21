#pragma once
#include "GameObjectCommands.h"
#include "Components/ScoreComponent.h"

namespace amu
{

	class ScoreCommand final : public GameObjectCommand
	{
	public:
		ScoreCommand(GameObject* gameObjectPtr, int scoreIncrease = 0)
			: GameObjectCommand(gameObjectPtr)
			, m_ScoreIncrease{ scoreIncrease }
		{
			m_ScoreComponentPtr = GetGameObject()->GetComponent<ScoreComponent>();
		}
		virtual ~ScoreCommand() = default;

		ScoreCommand(const ScoreCommand&) = delete;
		ScoreCommand& operator=(const ScoreCommand&) = delete;
		ScoreCommand(ScoreCommand&&) = delete;
		ScoreCommand& operator=(ScoreCommand&&) = delete;

		void Execute() override
		{
			m_ScoreComponentPtr->IncreaseScore(m_ScoreIncrease);
		}
	private:
		const int m_ScoreIncrease{ 1 };
		ScoreComponent* m_ScoreComponentPtr{ nullptr };
	};
}