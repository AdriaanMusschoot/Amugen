#ifndef AMU_CONTROLLER_WRAPPER_H
#define AMU_CONTROLLER_WRAPPER_H

#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include <tuple>
#include "GameObjectCommands.h"
#include "InputManager.h"

namespace amu
{

	class Controller final
	{
	public:
		Controller(int controllerIndex);
		~Controller();

		Controller(Controller const&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator= (Controller const&) = delete;
		Controller& operator= (Controller&&) = delete;

		void AddCommand(unsigned int button, InputManager::InputState state, std::unique_ptr<Command> commandPtr);
		void ProcessControllerInput();

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_ControllerImplPtr;

		int m_ControllerIndex;
	};

}

#endif //AMU_CONTROLLER_WRAPPER_H
