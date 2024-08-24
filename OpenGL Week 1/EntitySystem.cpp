/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : EntitySystem.cpp
Description : Entity system is a container and controller of the entities for the game
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "EntitySystem.h"
#include "Entity.h"
#include "Camera.h"
#include "GraphicsEntity.h"

EntitySystem::EntitySystem()
{
}

EntitySystem::EntitySystem(Scene* scene)
{
	m_scene = scene;
}

EntitySystem::~EntitySystem()
{
}

Scene* EntitySystem::getScene()
{
	return m_scene;
}

bool EntitySystem::createEntityInternal(Entity* entity, size_t id)
{
	auto ptr = std::unique_ptr<Entity>(entity);

	// Check if the entity is of type Camera
	if (dynamic_cast<Camera*>(entity)) {
		m_cameras.push_back(static_cast<Camera*>(entity));
	}
	// Check if the entity is of type GraphicsEntity
	else if (dynamic_cast<GraphicsEntity*>(entity)) {
		m_graphicsEntities.push_back(static_cast<GraphicsEntity*>(entity));
	}

	// Add the entity to the internal map
	m_entities[id].emplace(entity, std::move(ptr));

	// Initialize the entity
	entity->setId(id);
	entity->setEntitySystem(this);
	entity->onCreate();

	return true;
}

void EntitySystem::removeEntity(Entity* entity)
{
	m_entitiesToDestroy.emplace(entity);
}

void EntitySystem::onUpdate(float deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->getId()].erase(e);
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

void EntitySystem::onLateUpdate(float deltaTime)
{
	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onLateUpdate(deltaTime);
		}
	}
}

void EntitySystem::onFixedUpdate(float fixedDeltaTime)
{
	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onFixedUpdate(fixedDeltaTime);
		}
	}
}

std::vector<GraphicsEntity*> EntitySystem::getGraphicsEntities() const
{
	return m_graphicsEntities;
}

std::vector<Camera*> EntitySystem::getCameras() const
{
	return m_cameras;
}

void EntitySystem::clearEntities()
{
	// Clear the entities in the map
	m_entities.clear();

	// Clear the graphics entities vector
	m_graphicsEntities.clear();

	// Clear the cameras vector
	m_cameras.clear();

	m_entitiesToDestroy.clear();
}
