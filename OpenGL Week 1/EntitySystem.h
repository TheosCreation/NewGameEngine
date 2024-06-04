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
class Game;

/**
 * @class EntitySystem
 * @brief A container and controller of the entities for the game.
 */
class EntitySystem
{
public:
    /**
     * @brief Default constructor for the EntitySystem class.
     */
    EntitySystem();

    /**
     * @brief Constructor for the EntitySystem class with a game pointer.
     * @param game Pointer to the game instance.
     */
    EntitySystem(Game* game);

    /**
     * @brief Destructor for the EntitySystem class.
     */
    ~EntitySystem();

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
     * @brief Gets the game instance.
     * @return A pointer to the game instance.
     */
    Game* getGame();

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

    void onFixedUpdate();

    /**
     * @brief Map of entities categorized by their type ID.
     */
    std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;

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
     * @brief Pointer to the game instance.
     */
    Game* m_game = nullptr;
};