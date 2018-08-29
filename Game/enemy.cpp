#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "enemyControllerComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "explosion.h"
#include "animationComponent.h"
#include "waypointControllerComponent.h"
#include <vector>
#include "transformControllerComponent.h"
#include "timer.h"
#include "formation.h"


void Enemy::Create(const Info& info)
{
	m_info = info;

	SetTag("enemy");
	m_transform.position = Vector2D::zero;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.9f));

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string>animations;
	if (m_info.type == BEE) animations = { "enemy02A.png", "enemy02B.png" };
	if (m_info.type == BOSS) animations = { "enemy01A.png", "enemy01B.png" };
	if (m_info.type == BUG) animations = { "enemy03A.png", "enemy03B.png" };
	animationComponent->Create(animations, 1.0f / 10.0f, AnimationComponent::ePlayBack::LOOP);

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("attack", new AttackState(m_stateMachine));

	m_stateMachine->SetState("enter_path");
}

void Enemy::Update()
{
	Entity::Update();

	m_stateMachine->Update();

	/*Vector2D size = Renderer::Instance()->GetSize();
	if (m_transform.position.y > size.y)
	{
		float x = Math::GetRandomRange(0.0f, size.y);
		float y = -100.0f;
		m_transform.position = Vector2D(x, y);
	}*/

	
}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile")
		{
 			Event _event;
			_event.eventID = "add_score";
			_event.varient.asInteger = 100;
			_event.varient.type = Varient::INTEGER;

			EventManager::Instance()->SendGameMessage(_event);

			Explosion* explosion = m_scene->AddEntity<Explosion>();
			const ID& entity = GetTag();
			explosion->Create(entity, m_transform.position);

			SetState(Entity::DESTROY);
		}

		if (event.sender->GetTag() == "player")
		{
			SetState(Entity::DESTROY);
		}
	}
}


// Enter State
void EnterPathState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetEnterPath(m_owner->GetEntity<Enemy>()->m_info.side), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, true);
}

void EnterPathState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");
	}
}

void EnterPathState::Exit()
{

}

// Idles State
void IdleState::Enter()
{
	_TransformControllerComponent* controller = m_owner->GetEntity()->AddComponent<_TransformControllerComponent>();
	controller->Create(m_owner->GetEntity<Enemy>()->m_info.target, 180.0f, m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}
void IdleState::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		_TransformControllerComponent* controller = m_owner->GetEntity()->GetComponent<_TransformControllerComponent>();
		m_owner->GetEntity()->RemoveComponent(controller);
		m_owner->SetState("attack");
	}
}

void IdleState::Exit()
{
	
}

// Attack State
void AttackState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetRandomAttackPath(), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, false);
}

void AttackState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");
	}
}

void AttackState::Exit()
{
	m_owner->GetEntity()->GetTransform().position.y = -64.0f;
}

// Formation State
void EnterFormationState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	std::vector<Vector2D> target = { m_owner->GetEntity<Enemy>()->m_info.target };
	waypointController->Create(target, m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, false);
}

void EnterFormationState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("idle");
	}
}

void EnterFormationState::Exit()
{

}
