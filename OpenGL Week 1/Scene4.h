/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene4.h
Description : Scene4 class is a stripped-down class of the scene class to allow end user to create their own entities.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"
#include "MyPlayer.h"

/**
 * @class Scene4
 * @brief A stripped-down class of the scene class to allow the end user to create their own entities.
 */
class Scene4 : public Scene
{
public:
    /**
     * @brief Constructor for the Scene4 class.
     *
     * @param game A pointer to the Game instance, allowing access to game-wide functionalities.
     */
    Scene4(Game* game);

    /**
     * @brief Destructor for the Scene4 class.
     */
    ~Scene4();

    /**
     * @brief Called when the scene is created.
     * Initializes the scene by loading resources such as textures, meshes, and shaders.
     */
    virtual void onCreate();

    /**
     * @brief Called every frame to update the game logic.
     *
     * @param deltaTime The time elapsed since the last update in seconds.
     */
    virtual void onUpdate(float deltaTime);

    /**
     * @brief Called every frame to update the game at a fixed frame rate.
     *
     * @param fixedDeltaTime The time elapsed since the last fixed update in seconds.
     */
    virtual void onFixedUpdate(float fixedDeltaTime);

    /**
     * @brief Called every frame after rendering.
     * Can be overridden by derived classes to implement custom behavior.
     *
     * @param deltaTime The time elapsed since the last frame in seconds.
     */
    virtual void onLateUpdate(float deltaTime);

    /**
     * @brief Called every frame to update the graphics.
     */
    void onGraphicsUpdate();

    /**
     * @brief Called when quitting the scene.
     * Cleans up resources or performs necessary finalization.
     */
    virtual void onQuit() override;

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds since the scene started.

    // Initialize all VBOs here
    MeshEntity* m_ship = nullptr; // Pointer to the ship entity.
    TerrainEntity* m_terrain = nullptr; //Pointer to the terrain entity
    MyPlayer* m_player = nullptr; // Pointer to the player entity.
};