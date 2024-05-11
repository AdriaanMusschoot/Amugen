#ifndef AMU_CONTROLLER_WRAPPER_H
#define AMU_CONTROLLER_WRAPPER_H

#include <Windows.h>
#include <Xinput.h>
#include <vector>
#include <tuple>
#include "GameObjectCommands.h"
#include "InputManager.h"

namespace pacman
{

	class Controller final
	{
	public:
		Controller(int controllerIndex);
		~Controller();

		Controller(const Controller&) = delete;
		Controller& operator= (const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator= (const Controller&&) = delete;

		void AddCommand(unsigned int button, InputManager::InputState state, std::unique_ptr<Command> commandPtr);
		void ProcessControllerInput();

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_ControllerImplPtr;

		int m_ControllerIndex;
	};

}

#endif //AMU_CONTROLLER_WRAPPER_H
