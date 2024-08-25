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
	m_position = position;
}

void Entity::setRotation(const Vector3& rotation)
{
	m_rotation = rotation;
}

void Entity::setScale(const Vector3& scale)
{
	m_scale = scale;
}

void Entity::release()
{
	// Remove this entity from the EntitySystem
	m_entitySystem->removeEntity(this);
}

Vector3 Entity::getPosition()
{
	return m_position;
}

Vector3 Entity::getRotation()
{
	return m_rotation;
}

Vector3 Entity::getScale()
{
	return m_scale;
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

Mat4 Entity::getModelMatrix()
{
	Mat4 modelMatrix = glm::identity<Mat4>();

	//translate first
	modelMatrix = glm::translate(modelMatrix, m_position);

	//rotate around x
	modelMatrix = glm::rotate(modelMatrix, m_rotation.x, Vector3(1.0f, 0.0f, 0.0f));
	//rotate around y
	modelMatrix = glm::rotate(modelMatrix, m_rotation.y, Vector3(0.0f, 1.0f, 0.0f));
	//rotate around z
	modelMatrix = glm::rotate(modelMatrix, m_rotation.z, Vector3(0.0f, 0.0f, 1.0f));

	//scale
	modelMatrix = glm::scale(modelMatrix, m_scale);

	return modelMatrix;
}