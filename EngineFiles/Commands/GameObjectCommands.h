#ifndef AMU_GAME_OBJECT_COMMANDS_H
#define AMU_GAME_OBJECT_COMMANDS_H
#include "Command.h"
#include "GameObject.h"

namespace amu
{

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* actorPtr)
			: m_ActorPtr{ actorPtr }
		{}
		virtual ~GameObjectCommand() = default;

		GameObjectCommand(const GameObjectCommand&) = delete;
		GameObjectCommand(GameObjectCommand&&) = delete;
		GameObjectCommand& operator=(const GameObjectCommand&) = delete;
		GameObjectCommand& operator=(GameObjectCommand&&) = delete;
	protected:
		GameObject* GetGameObject() const { return m_ActorPtr; }
	private:
		GameObject* m_ActorPtr{ nullptr };
	};

}

#endif //AMU_GAME_OBJECT_COMMANDS_H