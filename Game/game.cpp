#include "game.h"
#include "engine.h"
#include "matrix22.h"
#include "matrix33.h"
#include "renderer.h"
#include "timer.h"
#include <iostream>
#include "text.h"
// Systems
#include "audioSystem.h"
#include "inputManager.h"
#include "textureManager.h"
#include "textManager.h"

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();

	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);

	text = TextManager::Instance()->CreateText("Hello", "..\\Content\\fonts\\Courier.ttf", 24, Color::red);

	InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	AudioSystem::Instance()->AddSound("horn", "..\\Content\\Sounds\\horn.wav");


	m_running = success;

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		AudioSystem::Instance()->PlaySound("laser");
		std::cout << "button\n";
	}

	if (InputManager::Instance()->GetActionButton("horn") == InputManager::eButtonState::PRESSED)
	{
		AudioSystem::Instance()->PlaySound("horn");
	}

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	float steer = InputManager::Instance()->GetActionAxisRelative("steer");
	angle += (steer * 20.0f) * Timer::Instance()->DeltaTime();
	
	//--INPUT--
	// LEFT RIGHT
	if ((keystate[SDL_SCANCODE_LEFT] == InputManager::eButtonState::PRESSED)
		|| (keystate[SDL_SCANCODE_LEFT] == InputManager::eButtonState::RELEASED))
	{
		angle -= 90.0f * Timer::Instance()->DeltaTime();
	}

	if ((keystate[SDL_SCANCODE_RIGHT] == InputManager::eButtonState::PRESSED)
		|| (keystate[SDL_SCANCODE_RIGHT] == InputManager::eButtonState::RELEASED))
	{
		angle += 90.0f * Timer::Instance()->DeltaTime();
	}
	// UP DOWN
	Vector2D force = Vector2D::zero;
	if ((keystate[SDL_SCANCODE_UP] == InputManager::eButtonState::PRESSED)
		|| (keystate[SDL_SCANCODE_UP] == InputManager::eButtonState::RELEASED))
	{
		force.y = -200.0f * Timer::Instance()->DeltaTime();
	}
	if ((keystate[SDL_SCANCODE_DOWN] == InputManager::eButtonState::PRESSED)
		|| (keystate[SDL_SCANCODE_DOWN] == InputManager::eButtonState::RELEASED))
	{
		force.y = 200.0f * Timer::Instance()->DeltaTime();
	}

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	// DRAW TEXT
	float x = InputManager::Instance()->GetActionAxisRelative("steer");
	std::string str = std::to_string(x);

	std::vector<Color>colors = { Color::red, Color::green, Color::white };
	text->SetText(str, colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	// DRAW CAR
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\Content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);

	Renderer::Instance()->EndFrame();
}
