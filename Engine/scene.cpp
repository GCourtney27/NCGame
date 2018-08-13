#include "scene.h"
#include "entity.h"
#include "collisionComponent.h"
#include "eventManager.h"
#include "renderComponent.h"
#include <assert.h>
#include <iostream>
#include <algorithm>

bool Scene::Initialize()
{
	return true;
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
	}
	m_entities.clear();
}

void Scene::Update()
{
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}

	// update collision
	std::vector<ICollisionComonent*>collisionComonents;
	for (Entity* entity : m_entities)
	{
		ICollisionComonent* CollisionComponent = entity->GetComponent<ICollisionComonent>();
		if (CollisionComponent)
		{
			collisionComonents.push_back(CollisionComponent);
		}
	}

	for (size_t i = 0; i < collisionComonents.size(); i++)
	{
		for (size_t j = i + 1; j < collisionComonents.size(); j++)
		{
			if (collisionComonents[i]->Intersects(collisionComonents[j]))
			{
				Event event;
				event.eventID = COLLISION_EVENT;

				event.receiver = collisionComonents[i]->GetOwner();
				event.sender = collisionComonents[j]->GetOwner();
				EventManager::Instance()->SendMessage(event);

				event.receiver = collisionComonents[j]->GetOwner();
				event.sender = collisionComonents[i]->GetOwner();
				EventManager::Instance()->SendMessage(event);
			}
		}
	}


	std::list<Entity*>::iterator iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		if ((*iter)->GetState() == Entity::DESTROY)
		{
			iter = RemoveEntity(*iter);
		}
		else
		{
			iter++;
		}
	}
}

void Scene::Draw()
{

	std::vector<IRenderComponent*>renderComonents;
	for (Entity* entity : m_entities)
	{
		IRenderComponent* renderComonent = entity->GetComponent<IRenderComponent>();
		if (renderComonent)
		{
			renderComonents.push_back(renderComonent);
		}
	}

	std::sort(renderComonents.begin(), renderComonents.end(), IRenderComponent::CompareDepth);
	for (IRenderComponent* renderComponent : renderComonents)
	{
		if (renderComponent->IsDepth())
		{
		}
			renderComponent->Draw();
	}
}

void Scene::AddEntity(Entity * entity)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end());
	assert(entity);

	m_entities.push_back(entity);
}

std::list<Entity*>::iterator Scene::RemoveEntity(Entity * entity, bool destroy)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());
	assert(entity);

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		if (destroy)
		{
			(*iter)->Destroy();
			delete *iter;
		}
	iter = m_entities.erase(iter);
	}

	return iter;
}

Entity* Scene::GetEntityWithID(const ID & id)
{
	Entity* entity = nullptr;

	for (Entity* _entity : m_entities)
	{
		if (*_entity == id)
		{
			entity = _entity;
			break;
		}
	}
	return entity;
}

std::vector<Entity*> Scene::GetEntitiesWithTag(const ID & tag)
{
	std::vector<Entity*> entities;
	
	for (Entity* entity : m_entities)
	{
		if (entity->GetTag() == tag)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}
