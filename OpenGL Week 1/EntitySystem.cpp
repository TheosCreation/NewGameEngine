#include "EntitySystem.h"
#include "Entity.h"
#include "Camera.h"
#include "GraphicsEntity.h"

EntitySystem::EntitySystem()
{
}

EntitySystem::EntitySystem(Game* game)
{
	m_game = game;
}

EntitySystem::~EntitySystem()
{
}

Game* EntitySystem::getGame()
{
	return m_game;
}

bool EntitySystem::createEntityInternal(Entity* entity, size_t id)
{
	auto ptr = std::unique_ptr<Entity>(entity);

	m_entities[id].emplace(entity, std::move(ptr));

	entity->m_id = id;
	entity->m_entitySystem = this;

	entity->onCreate();

	return true;
}

void EntitySystem::removeEntity(Entity* entity)
{
	m_entitiesToDestroy.emplace(entity);
}

void EntitySystem::update(float deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->m_id].erase(e);
	}
	m_entitiesToDestroy.clear();


	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onUpdate(deltaTime);
		}
	}
}

