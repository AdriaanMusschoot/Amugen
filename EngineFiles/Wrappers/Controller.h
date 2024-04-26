#ifndef _CONTROLLER_WRAPPER_

#define _CONTROLLER_WRAPPER_
#include "Windows.h"
#include "Xinput.h"
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

		Controller(const Controller&) = delete;
		Controller& operator= (const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator= (const Controller&&) = delete;

		void AddCommand(unsigned int button, InputManager::InputState state, std::unique_ptr<GameObjectCommand> commandPtr);
		void ProcessControllerInput();

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_ControllerImplPtr;

		int m_ControllerIndex;
	};

}

#endif
