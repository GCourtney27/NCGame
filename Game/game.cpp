// Files
#include "game.h"
#include "engine.h"
#include "matrix22.h"
#include "matrix33.h"
#include "renderer.h"
#include "timer.h"
#include "text.h"
#include "scene.h"
#include "ship.h"
#include "enemy.h"
// Systems
#include "audioSystem.h"
#include "inputManager.h"
#include "textureManager.h"
#include "textManager.h"
#include "fileSystem.h"

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathname("..\\Content\\Galaga\\");
	
	m_scene = new Scene();
	
	// SHIP
	Ship* ship = new Ship(m_scene);
	ship->Create(Vector2D(400.0f, 500.0f));
	m_scene->AddEntity(ship);
	// ENEMY
	Enemy* enemy = new Enemy(m_scene);
	enemy->Create(Vector2D(400.0f, 50.0f));
	m_scene->AddEntity(enemy);

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

	m_scene->Update();

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}
