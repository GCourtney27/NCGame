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

	

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_A) == InputManager::eAction::RELEASED)
	{
		std::cout << "released\n";
	}

	// INPUT
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	int x, y;
	if ((SDL_GetMouseState(&x, &y) && SDL_BUTTON(SDL_BUTTON_LEFT)) == (InputManager::eAction::PRESSED))
	{
		std::cout << "left mouse button pressed\n";
	}
	
	// --INPUT--
	// LEFT RIGHT
	if ((keystate[SDL_SCANCODE_LEFT] == InputManager::eAction::PRESSED)
		|| (keystate[SDL_SCANCODE_LEFT] == InputManager::eAction::RELEASED)) angle -= 90.0f * Timer::Instance()->DeltaTime();
	if ((keystate[SDL_SCANCODE_RIGHT] == InputManager::eAction::PRESSED)
		|| (keystate[SDL_SCANCODE_RIGHT] == InputManager::eAction::RELEASED)) angle += 90.0f * Timer::Instance()->DeltaTime();
	// UP DOWN
	Vector2D force = Vector2D::zero;
	if ((keystate[SDL_SCANCODE_UP] == InputManager::eAction::PRESSED)
		|| (keystate[SDL_SCANCODE_UP] == InputManager::eAction::RELEASED)) force.y = -200.0f * Timer::Instance()->DeltaTime();
	if ((keystate[SDL_SCANCODE_DOWN] == InputManager::eAction::PRESSED)
		|| (keystate[SDL_SCANCODE_DOWN] == InputManager::eAction::RELEASED)) force.y = 200.0f * Timer::Instance()->DeltaTime();

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	// DRAW TEXT
	text = TextManager::Instance()->CreateText("Hello", "..\\Content\\fonts\\Courier.ttf", 24, Color::red);
	std::vector<Color>colors = { Color::red, Color::green, Color::white };
	text->SetText("Hello World", colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	
	// DRAW CAR
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\Content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);


	Renderer::Instance()->EndFrame();

}


