#pragma once
// Headers
#include "engine.h"
#include "singleton.h"
#include "vector2D.h"
// Resources
#include <vector>
#include <map>

class InputManager : public Singleton<InputManager>
{

public:
	enum eButtonState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

	enum eDevice
	{
		KEYBOARD,
		MOUSE,
		CONTROLLER
	};

	enum eAxis
	{
		X,
		Y
	};

	struct InputInfo
	{
		int id;
		eDevice device;
		int index;
	};

	struct ControllerInfo
	{
		SDL_GameController * controller;

		Uint8 buttonState[SDL_CONTROLLER_BUTTON_MAX];
		Uint8 prevButtonState[SDL_CONTROLLER_BUTTON_MAX];
		float axis[SDL_CONTROLLER_AXIS_MAX];
		float prevAxis[SDL_CONTROLLER_AXIS_MAX];
	};

public:


	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void AddAction(const std::string& action, int id, eDevice device, int index = 0);
	eButtonState GetActionButton(const std::string action);
	float GetActionAxisAbsolute(const std::string action);
	float GetActionAxisRelative(const std::string action);

	eButtonState GetButtonState(int id, eDevice device = eDevice::KEYBOARD, int index = 0);
	float GetAxisAbsolute(int id, eDevice device = eDevice::MOUSE, unsigned int index = 0);
	float GetAxisRelative(int id, eDevice device = eDevice::MOUSE, unsigned int index = 0);


protected:
	bool GetButtonDown(int id, eDevice device, unsigned int index = 0);
	bool GetPreviousButtonDown(int id, eDevice device, unsigned int index = 0);

public:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
	// Keyboard
	Uint8* m_keystate;
	Uint8* m_prevKeystate;
	int m_numKeys;

	// Mouse
	Uint32 m_mouseButtonState;
	Uint32 m_prevMouseButtonState;
	Vector2D m_mousePosition;
	Vector2D m_prevMousePosition;

	// Controller
	std::vector<ControllerInfo> m_controllers;

	std::map<std::string, InputInfo> m_actions;
};