#include <SDL.h>
#include "Singletons/InputManager.h"
#include "Singletons/GUI.h"
#include "Wrappers/Controller.h"

#include "Wrappers/Controller.h"

amu::InputManager::InputManager()
	: m_ControllerArr{ std::make_unique<Controller>(0), std::make_unique<Controller>(1) }

{
}

amu::InputManager::~InputManager()
{
}

void amu::InputManager::AddCommandController(unsigned int controllerIdx, unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
{
	for (size_t idx{}; idx < m_ControllerArr.size(); ++idx)
	{
		if (idx == controllerIdx)
		{
			m_ControllerArr[idx]->AddCommand(button, state, std::move(commandPtr));
		}
	}
}

void amu::InputManager::AddCommandKeyboard(unsigned int button, InputState state, std::unique_ptr<GameObjectCommand> commandPtr)
{
	m_KeyboardCommandPtrVec.emplace_back(std::make_tuple(button, state, std::move(commandPtr)));
}

bool amu::InputManager::ProcessInput()
{
	////////////////////////////////////////
	///////////Xbox Input handling
	////////////////////////////////////////
	for (const auto& controllerUPtr : m_ControllerArr)
	{
		controllerUPtr->ProcessControllerInput();
	}

	////////////////////////////////////////
	///////////Keyboard and Mouse Input handling
	////////////////////////////////////////
	m_PreviousStateKeyboard = m_CurrentStateKeyboard;

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			m_CurrentStateKeyboard[e.key.keysym.sym] = true;
		}
		if (e.type == SDL_KEYUP)
		{
			m_CurrentStateKeyboard[e.key.keysym.sym] = false;
		}
		if (GUI::GetInstance().ProcessEvent(&e))
		{
			continue;
		}
	}
	
	for (const auto& [button, state, command] : m_KeyboardCommandPtrVec)
	{
		const bool buttonChangedThisFrame{ m_CurrentStateKeyboard[button] != m_PreviousStateKeyboard[button] };
		const bool buttonPressedThisFrame{ buttonChangedThisFrame && m_CurrentStateKeyboard[button] };
		const bool buttonReleasedThisFrame{ buttonChangedThisFrame && !m_CurrentStateKeyboard[button] };
		switch (state)
		{
		case InputState::Pressed:
			if (buttonPressedThisFrame && buttonChangedThisFrame)
			{
				command->Execute();
			}
			break;
		case InputState::Released:
			if (buttonReleasedThisFrame && buttonChangedThisFrame)
			{
				command->Execute();
			}
			break;
		case InputState::Held:
			if (m_CurrentStateKeyboard[button])
			{
				command->Execute();
			}
			break;
		}
	}

	return true;
}

