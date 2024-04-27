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
		enum class Key
		{
			W = 119,
			A = 79,
			S = 115,
			D = 100
		};

		enum class Button
		{
			DPadUp,
			DPadDown,
			DPadLeft,
			DPadRight
		};

		enum class InputState
		{
			Pressed,
			Released,
			Held
		};

		InputManager();
		~InputManager();

		void AddCommandController(unsigned int controllerIdx, unsigned int button, InputState state, std::unique_ptr<Command> commandPtr);
		void AddCommandKeyboard(Key key, InputState state, std::unique_ptr<Command> commandPtr);

		bool ProcessInput();
	private:
		std::array<std::unique_ptr<Controller>, 2> m_ControllerArr{};


		std::vector<std::tuple<unsigned int, InputState, std::unique_ptr<Command>>> m_KeyboardCommandPtrVec;

		std::map<int, bool> m_PreviousStateKeyboard;
		std::map<int, bool> m_CurrentStateKeyboard;
	};

}

#endif