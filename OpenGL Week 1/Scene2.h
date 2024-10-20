/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene2.h
Description : A stripped-down class of the scene class to allow the end user to create their own entities.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"
#include "MyPlayer.h"

/**
 * @class Scene2
 * @brief A stripped-down class of the scene class to allow the end user to create their own entities.
 */
class Scene2 : public Scene
{
public:
    /**
     * @brief Constructor for the Scene2 class.
     */
    Scene2(Game* game);

    /**
     * @brief Destructor for the Scene2 class.
     */
    ~Scene2();

    /**
     * @brief Called when the game is created.
     */
    virtual void onCreate();

    /**
     * @brief Called every frame to update the game logic.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onUpdate(float deltaTime);

    /**
     * @brief Called every frame to update the game at a fixed frame rate.
     */
    virtual void onFixedUpdate(float fixedDeltaTime);

    /**
     * @brief Called every frame after rendering.
     * Can be overridden by derived classes to implement custom behavior.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void onLateUpdate(float deltaTime);

    /**
     * @brief Called when quitting the scene.
     * Cleans up resources or performs necessary finalization.
     */
    virtual void onQuit() override;

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds

    // Initialize all VBOs here
    MyPlayer* m_player = nullptr; // Pointer to the player entity
    TerrainEntity* m_terrain = nullptr; // Pointer to the terrain entity
    MeshEntity* m_ship = nullptr; // Pointer to the ship entity
    ShaderPtr m_outlineShader = nullptr; // Pointer to the outline shader
};