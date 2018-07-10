#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>

class InputManager : public Singleton<InputManager>
{

public:
	enum eAction
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};
public:


	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	eAction GetButtonAction(SDL_Scancode scancode);

public:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
	Uint8* m_keystate;
	Uint8* m_prevKeystate;
	int m_numKeys;
};