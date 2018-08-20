#include "enemyFlightAnimation.h"
#include "spriteComponent.h"
#include "animationComponent.h"

void EnemyFlightAnimation::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(1.5f, 1.5f);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string>textureNames = {"enemy01A.png", "enemy01B.png"};
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayBack::LOOP);

}

void EnemyFlightAnimation::Update()
{
	Entity::Update();
}
