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
}

void Entity::setRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
}

void Entity::setScale(const glm::vec3& scale)
{
	m_scale = scale;
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

glm::mat4 Entity::getModelMatrix()
{
	glm::mat4 modelMatrix = glm::identity<glm::mat4>();

	//translate first
	modelMatrix = glm::translate(modelMatrix, m_position);

	//rotate around z
	modelMatrix = glm::rotate(modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	//rotate around y
	modelMatrix = glm::rotate(modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate around x
	modelMatrix = glm::rotate(modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	//scale
	modelMatrix = glm::scale(modelMatrix, m_scale);

	return modelMatrix;
}
