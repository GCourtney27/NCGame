#pragma once
#include "component.h"
#include "engine.h"
#include <vector>

class Texture;

class ENGINE_API AnimationComponent : public Component
{
public:
	enum ePlayBack
	{
		LOOP,
		ONE_TIME,
		ONE_TIME_DESTROY,
		PING_PONG
	};

public:
	AnimationComponent(Entity* owner) : Component(owner) {}

	void Create(std::vector<std::string>& textureNames, float rate, ePlayBack playback = ePlayBack::LOOP);
	void Destroy();
	void Update();

	Texture* GetTexture();

protected:
	std::vector<Texture*> m_textures;
	ePlayBack m_playback = ePlayBack::LOOP;
	float m_rate = 0.0f;
	float m_timer = 0.0f;
	size_t m_frame = 0;
	int m_direction = 1;
};