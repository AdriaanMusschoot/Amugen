#ifndef _INPUT_MANAGER_

#define _INPUT_MANAGER_
#include "Singleton.h"
#include "GameObjectCommands.h"
#include <map>
#include <array>

namespace amu
{
	class Controller;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputState
		{
			Pressed,
			Released,
			Held
		};
		InputManager();
		~InputManager();

		void AddCommandController(unsigned int controllerIdx, unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr);
		void AddCommandKeyboard(unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr);

		bool ProcessInput();
	private:
		std::array<std::unique_ptr<Controller>, 2> m_ControllerArr{};


		std::vector<std::tuple<unsigned int, InputState, std::unique_ptr<GameObjectCommand>>> m_KeyboardCommandPtrVec;

		std::map<int, bool> m_PreviousStateKeyboard;
		std::map<int, bool> m_CurrentStateKeyboard;
	};

}

#endif _INPUT_MANAGER_