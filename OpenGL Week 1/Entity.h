/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Entity.h
Description : Entity class that represents an object for OpenGl with its own update and onCreate functions.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"
#include "Math.h"
#include "Game.h"

class EntitySystem;
/**
 * @class Entity
 * @brief Represents an object for OpenGl with its own update and onCreate functions.
 */
class Entity
{
public:
    /**
     * @brief Constructor for the Entity class.
     */
	Entity();

    /**
     * @brief Destructor for the Entity class.
     */
	virtual ~Entity();

    /**
     * @brief Gets the unique identifier of the entity.
     * @return The unique identifier of the entity.
     */
    size_t getId();

    /**
     * @brief Sets the unique identifier of the entity.
     * @param id The unique identifier to set.
     */
    void setId(size_t id);

	/**
	 * @brief Gets the position of the entity in 3D space.
	 * @return The position of the entity.
	 */
	glm::vec3 getPosition();

    /**
     * @brief Sets the position of the entity in 3D space.
     * @param position The new position to set.
     */
    void setPosition(const glm::vec3& position);

    /**
     * @brief Gets the rotation of the entity in 3D space.
     * @return The rotation of the entity.
     */
    glm::vec3 getRotation();

    /**
     * @brief Sets the rotation of the entity in 3D space.
     * @param rotation The new rotation to set.
     */
    void setRotation(const glm::vec3& rotation);

    /**
     * @brief Gets the scale of the entity.
     * @return The scale of the entity.
     */
    glm::vec3 getScale();

    /**
     * @brief Sets the scale of the entity.
     * @param scale The new scale to set.
     */
    void setScale(const glm::vec3& scale);

    /**
     * @brief Gets the EntitySystem that manages this entity.
     * @return A pointer to the EntitySystem.
     */
	EntitySystem* getEntitySystem();

    /**
     * @brief Sets the EntitySystem that manages this entity.
     * @param entitySystem A pointer to the EntitySystem.
     */
	void setEntitySystem(EntitySystem* entitySystem);

    /**
     * @brief Gets the model matrix representing the entity's transformation.
     * @return The model matrix.
     */
	glm::mat4 getModelMatrix();

    /**
     * @brief Releases the entity, preparing it for destruction.
     */
	void release();

    /**
     * @brief Gets the Game instance associated with this entity.
     * @return A pointer to the Game instance.
     */
	Game* getGame();

    /**
     * @brief Called when the entity is created.
     * Can be overridden by derived classes to perform initialization.
     */
	virtual void onCreate() {}

    /**
     * @brief Called every frame to update the entity.
     * Can be overridden by derived classes to implement custom behavior.
     * @param deltaTime The time elapsed since the last frame.
     */
	virtual void onUpdate(float deltaTime) {}

    /**
     * @brief Called every frame to update the entity at a fixed frame rate.
     * Can be overridden by derived classes to implement custom behavior.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void onFixedUpdate() {}

    /**
     * @brief Called every frame after all Update functions have been called.
     * Can be overridden by derived classes to implement custom behavior.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void onLateUpdate(float deltaTime) {}

protected:
	glm::vec3 m_position{}; //The position of the entity in 3D space.
	glm::vec3 m_rotation{}; //The rotation of the entity in 3D space.
	glm::vec3 m_scale = glm::vec3(1, 1, 1); //The scale of the entity.

	EntitySystem* m_entitySystem = nullptr; //Pointer to the EntitySystem managing this entity.

private:
	size_t m_id = 0; //Unique identifier for the entity.
};
