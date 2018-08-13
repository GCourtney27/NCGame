#include "animationComponent.h"
#include "texture.h"
#include "timer.h"
#include "entity.h"
#include "spriteComponent.h"

void AnimationComponent::Create(std::vector<std::string>& textureNames, float rate)
{
	for (std::string textureName : textureNames)
	{
		Texture* texture = new Texture();
		texture->Create(textureName);

		m_textures.push_back(texture);
	}

	m_rate = rate;
}

void AnimationComponent::Destroy()
{
	for (Texture* texture : m_textures)
	{
		texture->Destroy();
		delete texture;
	}

	m_textures.clear();
}

void AnimationComponent::Update()
{
	m_timer = m_timer + Timer::Instance()->DeltaTime();
	if (m_timer >= m_rate)
	{
		m_timer = m_timer - m_rate;
		m_frame++;
		if (m_frame >= m_textures.size())
		{
			m_frame = 0;
		}
	}
	SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
	if (spriteComponent)
	{
		spriteComponent->SetTexture(GetTexture());

	}
}

Texture * AnimationComponent::GetTexture()
{

	return m_textures[m_frame];
}
