#include "Entity.h"
#include "EntitySystem.h"
#include "Game.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::setPosition(const glm::vec3& position)
{
	m_position = position;
	processWorldMatrix();
}

void Entity::setRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
	processWorldMatrix();
}

void Entity::setScale(const glm::vec3& scale)
{
	m_scale = scale;
	processWorldMatrix();
}

void Entity::release()
{
	m_entitySystem->removeEntity(this);
}

glm::vec3 Entity::getPosition()
{
	return m_position;
}

glm::vec3 Entity::getRotation()
{
	return m_rotation;
}

glm::vec3 Entity::getScale()
{
	return m_scale;
}

EntitySystem* Entity::getEntitySystem()
{
	return m_entitySystem;
}

Game* Entity::getGame()
{
	return getEntitySystem()->getGame();
}

void Entity::getWorldMatrix(glm::mat4& world)
{
	world = m_world;
}

void Entity::processWorldMatrix()
{
	m_world = glm::mat4(1.0f);

	//translate first
	m_world = glm::translate(m_world, m_position);

	//rotate around z
	m_world = glm::rotate(m_world, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	//rotate around y
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate around x
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	//scale
	m_world = glm::scale(m_world, m_scale);
}
