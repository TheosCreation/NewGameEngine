/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene1.h
Description : 
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"
#include "MyPlayer.h"

/**
 * @class Scene1
 * @brief 
 */
class Scene1 : public Scene
{
public:
    /**
     * @brief Constructor for the Scene1 class.
     */
    Scene1(Game* game);

    /**
     * @brief Destructor for the Scene1 class.
     */
    ~Scene1();

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
    virtual void onQuit() override;

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds

    // Initialize all VBOs here
    MyPlayer* m_player = nullptr; //Pointer to the player entity
    TerrainEntity* m_terrain = nullptr; //Pointer to the terrain entity
    MeshEntity* m_ship = nullptr; //Pointer to the ship entity

    ShaderPtr m_outlineShader = nullptr;
};