#pragma once
#include "GameObjectCommands.h"
#include "Components/HealthComponent.h"
namespace amu
{

	class DamageCommand final : public GameObjectCommand
	{
	public:
		DamageCommand(GameObject* gameObjectPtr, int damage)
			: GameObjectCommand(gameObjectPtr)
			, m_Damage{ damage }
		{
			m_HealthComponentPtr = GetGameObject()->GetComponent<HealthComponent>();
		}
		virtual ~DamageCommand() = default;

		DamageCommand(const DamageCommand&) = delete;
		DamageCommand& operator=(const DamageCommand&) = delete;
		DamageCommand(DamageCommand&&) = delete;
		DamageCommand& operator=(DamageCommand&&) = delete;

		void Execute() override
		{
			m_HealthComponentPtr->ReduceHealth(m_Damage);
		}
	private:
		const int m_Damage;
		HealthComponent* m_HealthComponentPtr{ nullptr };
	};
}