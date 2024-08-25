/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Entity.cpp
Description : Entity class that represents an object for OpenGl with its own update and onCreate functions.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Entity.h"
#include "EntitySystem.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

size_t Entity::getId()
{
	return m_id;
}

void Entity::setId(size_t id)
{
	m_id = id;
}

void Entity::setPosition(const Vector3& position)
{
	m_transform.position = position;
}

void Entity::setRotation(const Quaternion& rotation)
{
	m_transform.rotation = rotation;
}

void Entity::setScale(const Vector3& scale)
{
	m_transform.scale = scale;
}

Mat4 Entity::getModelMatrix() const
{
	return m_transform.GetMatrix();
}

void Entity::release()
{
	// Remove this entity from the EntitySystem
	m_entitySystem->removeEntity(this);
}

Vector3 Entity::getPosition()
{
	return m_transform.position;
}

Quaternion Entity::getRotation()
{
	return m_transform.rotation;
}

Vector3 Entity::getScale()
{
	return m_transform.scale;
}

void Entity::setEntitySystem(EntitySystem* entitySystem)
{
	// Set the EntitySystem managing this entity
	m_entitySystem = entitySystem;
}

EntitySystem* Entity::getEntitySystem()
{
	return m_entitySystem;
}