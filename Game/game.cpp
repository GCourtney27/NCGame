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
#include "spriteComponent.h"
#include "textComponent.h"
#include "eventManager.h"
// Systems
#include "audioSystem.h"
#include "inputManager.h"
#include "textureManager.h"
#include "textManager.h"
#include "fileSystem.h"
#include "animationComponent.h"
#include "stateMachine.h"
#include "states.h"

Vector2D position(400.0f, 300.0f);
float angle = 0.0f;
Text* text;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathname("..\\Content\\Galaga\\");

	EventManager::Instance()->SetGameEventReceiver(this);

	m_scene = new Scene();
	m_stateMachine = new StateMachine(m_scene);

	m_stateMachine->AddState("title", new TitleState(m_stateMachine));
	m_stateMachine->AddState("game", new GameState(m_stateMachine));

	m_stateMachine->SetState("title");

	Entity* entity = new Entity(m_scene, "score");
	entity->GetTransform().position = Vector2D(20.0f, 20.0f);
	TextComponent* textComponent = entity->AddComponent<TextComponent>();
	textComponent->Create("hello", "emulogic.ttf", 18, Color::white);
	textComponent->SetDepth(100);
	m_scene->AddEntity(entity);

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

	Entity* scoreEntity = m_scene->GetEntityWithID("score");
	if (scoreEntity)
	{
		TextComponent* textComponent = scoreEntity->GetComponent<TextComponent>();
		std::string score = std::to_string(m_score);
		while (score.length() < 5)
		{
			score = "0" + score;
		}
		textComponent->SetText(score);
	}

	m_stateMachine->Update();

	Renderer::Instance()->SetColor(Color::black);
	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.eventID == "add_score")
	{
		m_score = m_score + event.varient.asInteger;
	}
}
