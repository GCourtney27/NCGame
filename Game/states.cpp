#include "states.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "entity.h"
#include "inputManager.h"
#include "enemy.h"
#include "ship.h"
#include "formation.h"
#include "timer.h"

// Title State
void TitleState::Enter()
{
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = entity->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);

	m_credits = 0;
}
void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("enter_stage");
	}
}
void TitleState::Exit()
{
	Entity* entity = m_owner->GetScene()->GetEntityWithID("title");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
}

// Game State
void GameState::Enter()
{

}
void GameState::Update()
{

}
void GameState::Exit()
{

}

// Enter Stage State
void EnterStageState::Enter()
{
	// SHIP
	Ship* ship = new Ship(m_owner->GetScene(), "player");
	ship->Create(Vector2D(400.0f, 500.0f));
	m_owner->GetScene()->AddEntity(ship);

	Timer::Instance()->Reset();
	Formation* formation =dynamic_cast<Formation*> (m_owner->GetScene()->GetEntityWithID("formation"));
	if (formation == nullptr)
	{
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		ID* id = new ID("middle_phase");
		formation->Create(*id);
	}
}
void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*> (m_owner->GetScene()->GetEntityWithID("formation"));
	formation->Update();
}
void EnterStageState::Exit()
{

}
