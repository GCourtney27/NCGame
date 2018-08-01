#include "entity.h"
#include "renderComponent.h"
#include <assert.h>

void Entity::Destroy()
{
	for (Component* component : m_components)
	{
		component->Destroy();
		delete component;
	}

	m_components.clear();
}

void Entity::Update()
{
	for (Component* component : m_components)
	{
		component->Update();
	}
}

void Entity::Draw()
{
	IRenderComponent* renderComponent = GetComponent<IRenderComponent>();
	if (renderComponent)
	{
		renderComponent->Draw();
	}
}

void Entity::AddComponent(Component * component)
{
	assert(component);
	assert(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

	m_components.push_back(component);
}

void Entity::RemoveComponent(Component * component)
{
	assert(std::find(m_components.begin(), m_components.end(), component) != m_components.end());

	auto iter = std::find(m_components.begin(), m_components.end(), component);
	delete *iter;
	m_components.erase(iter);
}
