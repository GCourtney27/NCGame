#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "inputManager.h"
#include "audioSystem.h"
#include "matrix22.h"
#include "timer.h"
#include "text.h"
#include "textManager.h"
#include "SDL_ttf.h"
#include <cassert>
#include <iostream>

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;
bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);

	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);

	AudioSystem::Instance()->AddSound("laser", "..\\Content\\Sounds\\laser.wav");
	//AudioSystem::Instance()->PlaySound("laser");
	
	text = TextManager::Instance()->CreateText("Hello", "..\\Content\\fonts\\Courier.ttf", 24, Color::red);

	return true;
}

void Engine::Shutdown()
{
	AudioSystem::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	Timer::Instance()->Shutdown();

	SDL_DestroyWindow(m_window);
	TTF_Quit();
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(1.0f);
	InputManager::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}

	}

	SDL_PumpEvents();


	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		AudioSystem::Instance()->PlaySound("laser");
		std::cout << "button\n";
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


