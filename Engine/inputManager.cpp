#include "inputManager.h"
#include <string.h>

bool InputManager::Initialize(Engine * engine)
{
	m_engine = engine;

	SDL_GetKeyboardState(&m_numKeys);
	m_keystate = new Uint8[m_numKeys];
	m_prevKeystate = new Uint8[m_numKeys];

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);
	memcpy(m_prevKeystate, m_keystate, m_numKeys);

	return true;
}

void InputManager::Shutdown()
{
	delete m_keystate;
	delete m_prevKeystate;
}

void InputManager::Update()
{
	memcpy(m_prevKeystate, m_keystate, m_numKeys);
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);
}

InputManager::eAction InputManager::GetButtonAction(SDL_Scancode scancode)
{
	eAction action = eAction::IDLE;

	if (m_keystate[scancode])
	{
		action = (m_prevKeystate[scancode]) ? eAction::HELD : eAction::PRESSED;
	}
	else
	{
		action = (m_prevKeystate[scancode]) ? eAction::RELEASED : eAction::IDLE;
	}

	return action;
}