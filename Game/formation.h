#pragma once
#include "entity.h"
#include "enemy.h"


//#define Path std::vector<Vector2D>;
//typedef std::vector<Vector2D> Path;

class Formation : public Entity
{

public:
	using Path = std::vector<Vector2D>;

public:
	struct Info
	{
		Enemy::Info enemyInfo;
		float enterTime;
		bool isActive;
	};

public:
	Formation(Scene* scene, const ID& id) : Entity(scene, id) {}
	virtual ~Formation() {}

	void Create(ID& type);
	void Update();
	void Destroy();

	const Path& GetEnterPath(Enemy::eSide side) { return m_enterPaths[side]; }
	const Path& GetRandomAttackPath();

protected:
	std::vector<Info> m_formation;
	float m_timer = 0.0f;

	Path m_enterPaths[2];
	std::vector<Path> m_attackPaths;

};