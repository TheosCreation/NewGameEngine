/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : EntitySystem.h
Description : Entity system is a container and controller of the entities for the game
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"
#include "Math.h"
#include <map>
#include <set>

// Forward declarations of classes
class Entity;
class GraphicsEntity;
class Camera;
class Scene;

/**
 * @class EntitySystem
 * @brief A container and controller of the entities for the scene.
 */
class EntitySystem
{
public:
    /**
     * @brief Default constructor for the EntitySystem class.
     */
    EntitySystem();

    /**
     * @brief Constructor for the EntitySystem class with a scene pointer.
     * @param scene Pointer to the Scene.
     */
    EntitySystem(Scene* scene);

    /**
     * @brief Destructor for the EntitySystem class.
     */
    ~EntitySystem();

    Scene* getScene();

    /**
     * @brief Creates an entity of type T.
     * @tparam T The type of entity to create.
     * @return A pointer to the created entity.
     */
    template <typename T>
    T* createEntity()
    {
        static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity class");
        auto id = typeid(T).hash_code();
        auto e = new T();
        if (createEntityInternal(e, id))
            return e;
        return nullptr;
    }

    /**
     * @brief Removes an entity from the system.
     * @param entity Pointer to the entity to remove.
     */
    void removeEntity(Entity* entity);

    /**
     * @brief Updates the entity system.
     * @param deltaTime The time elapsed since the last update.
     */
    void onUpdate(float deltaTime);

    void onLateUpdate(float deltaTime);
    void onGraphicsUpdate(float deltaTime, UniformData _data);

    /**
     * @brief Called every frame to update the entity system at a fixed frame rate.
     */
    void onFixedUpdate(float fixedDeltaTime);

    /**
     * @brief Gets all graphics entities.
     * @return A vector of pointers to the graphics entities.
     */
    std::vector<GraphicsEntity*> getGraphicsEntities() const;

    /**
     * @brief Gets all camera entities.
     * @return A vector of pointers to the camera entities.
     */
    std::vector<Camera*> getCameras() const;

    /**
     * @brief Map of entities categorized by their type ID.
     */
    std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;

    void clearEntities();

private:
    /**
     * @brief Internal function to create an entity.
     * @param entity Pointer to the entity to create.
     * @param id The type ID of the entity.
     * @return True if the entity was created successfully, false otherwise.
     */
    bool createEntityInternal(Entity* entity, size_t id);

    /**
     * @brief Set of entities scheduled for destruction.
     */
    std::set<Entity*> m_entitiesToDestroy;

    /**
     * @brief Vector of all graphics entities.
     */
    std::vector<GraphicsEntity*> m_graphicsEntities;

    /**
     * @brief Vector of all camera entities.
     */
    std::vector<Camera*> m_cameras;

    /**
     * @brief Pointer to the scene instance.
     */
    Scene* m_scene = nullptr;
};