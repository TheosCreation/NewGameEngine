/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Entity.h
Description : entity is an obj that has its own update and start function
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"
#include "Math.h"
#include "Game.h"

class EntitySystem;
class Entity
{
public:
	Entity();
	virtual ~Entity();
public:
	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setScale(const glm::vec3& scale);
	glm::vec3 getPosition();
	glm::vec3 getRotation();
	glm::vec3 getScale();

	EntitySystem* getEntitySystem();
	glm::mat4 getModelMatrix();
	void release();

	Game* getGame();
protected:
	virtual void onCreate() {}
	virtual void onUpdate(float deltaTime) {}

protected:
	glm::vec3 m_position{};
	glm::vec3 m_rotation{};
	glm::vec3 m_scale = glm::vec3(1, 1, 1);

	size_t m_id = 0;
	EntitySystem* m_entitySystem = nullptr;

	friend class EntitySystem;
};
