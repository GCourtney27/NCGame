#include "explosion.h"
#include "animationComponent.h"
#include "spriteComponent.h"
#include "audioSystem.h"

void Explosion::Create(const ID& explosionType, const Vector2D& position)
{
	// Player Explosion
	if (explosionType == "player")
	{
		m_transform.position = position;
		m_transform.scale = Vector2D(2.0f, 2.0f);
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("", Vector2D(0.5f, 0.5f));
		AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
		std::vector<std::string>textureNames = { "ship-explosion01.png", "ship-explosion02.png", "ship-explosion03.png", "ship-explosion04.png" };
		animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayBack::ONE_TIME_DESTROY);

		AudioSystem::Instance()->AddSound("explosion", "ship-explosion.wav");
		AudioSystem::Instance()->PlaySound("explosion");
	}
	

	// Enemy Explosion
	if (explosionType == "enemy")
	{
		m_transform.position = position;
		m_transform.scale = Vector2D(2.0f, 2.0f);
		SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
		spriteComponent->Create("", Vector2D(0.5f, 0.5f));
		AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
		std::vector<std::string>textureNames = { "enemy-explosion01.png", "enemy-explosion02.png", "enemy-explosion03.png", "enemy-explosion04.png", "enemy-explosion05.png" };
		animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayBack::ONE_TIME_DESTROY);

		AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
		AudioSystem::Instance()->PlaySound("explosion");
	}
	
}

void Explosion::Update()
{
	Entity::Update();
}
