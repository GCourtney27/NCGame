#pragma once
#include "id.h"
#include "engine.h"
#include <vector>
#include <list>
#include <assert.h>

class Entity;

class ENGINE_API Scene
{
public:
	Scene() {}
	~Scene() {}

	bool Initialize();
	void Shutdown();
	void Update();
	void Draw();

	template<typename T>
	T* AddEntity(const ID& id = ID())
	{
		T* entity = new T(this, id);
		//assert(dynamic_cast<Component*>(entity));

		m_entities.push_back(entity);

		return entity;
	}

	void AddEntity(Entity* entity);
	std::list<Entity*>::iterator RemoveEntity(Entity* entity, bool destroy = true);

	Entity* GetEntityWithID(const ID& id);
	std::vector<Entity*>GetEntitiesWithTag(const ID& tag);

protected:
	std::list<Entity*> m_entities;
};