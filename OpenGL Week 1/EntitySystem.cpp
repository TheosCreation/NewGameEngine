#include "EntitySystem.h"
#include "Entity.h"
#include "Camera.h"
#include "GraphicsEntity.h"

EntitySystem::EntitySystem()
{
}

EntitySystem::~EntitySystem()
{
}

//bool EntitySystem::createEntityInternal(Entity* entity, size_t id)
//{
//	auto ptr = std::unique_ptr<Entity>(entity);
//	m_entities[id].emplace(entity, std::move(ptr));
//	//entity->m_game = this;
//	entity->m_id = id;
//	entity->m_entitySystem = this;
//
//	entity->onCreate();
//
//	return true;
//}

bool EntitySystem::createEntityInternal(Entity* entity, size_t id, Game* game)
{
	auto ptr = std::unique_ptr<Entity>(entity);
	auto camId = typeid(Camera).hash_code();
	entity->m_game = game;
	if (id == camId)
	{
		auto it = m_entities.find(camId);
		if (it != m_entities.end())
		{
			if (it->second.size()) return false;
			it->second.emplace(entity, std::move(ptr));
		}
		else 
		{
			m_entities[id].emplace(entity, std::move(ptr));
		}
	}
	else
	{
		m_entities[id].emplace(entity, std::move(ptr));
	}
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

