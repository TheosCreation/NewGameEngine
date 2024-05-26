/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : MyGame.h
Description : MyGame class is a stripped down class of the base game class to be able for end user to create their own entities
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"
#include "MyPlayer.h"

/**
 * @class MyGame
 * @brief A stripped-down class of the base game class to allow end user to create their own entities.
 */
class MyGame : public Game
{
public:
    /**
     * @brief Constructor for the MyGame class.
     */
    MyGame();

    /**
     * @brief Destructor for the MyGame class.
     */
    ~MyGame();

    /**
     * @brief Called when the game is created.
     */
    virtual void onCreate();

    /**
     * @brief Called every frame to update the game logic.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onUpdate(float deltaTime);

    virtual void onLateUpdate(float deltaTime);

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds

    // Initialize all VBOs here
    SkyboxEntity* m_skybox = nullptr; //Pointer to the skybox entity
    MeshEntity* m_statue = nullptr; //Pointer to the statue entity
    MeshEntity* m_ground = nullptr; //Pointer to the ground entity
    InstancedMeshEntity* m_instancedTree = nullptr; //Pointer to the instanced tree entity
    MyPlayer* m_player = nullptr; //Pointer to the player entity
    QuadEntity* m_button = nullptr; //Pointer to the button entity

    float m_rotz = 0; //Rotation around the z-axis
    float m_roty = 0; //Rotation around the y-axis
    float m_uiScaleX = 2.0; //UI scale factor for the x-axis
    float m_uiScaleY = -2.0; //UI scale factor for the y-axis
};