#include "Entity.h"
#include "EntitySystem.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::release()
{
	m_entitySystem->removeEntity(this);
}

EntitySystem* Entity::getEntitySystem()
{
	return m_entitySystem;
}