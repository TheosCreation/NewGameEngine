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
 * @class MyScene
 * @brief A stripped-down class of the scene class to allow end user to create their own entities.
 */
class Scene4 : public Scene
{
public:
    /**
     * @brief Constructor for the MyGame class.
     */
    Scene4(Game* game);

    /**
     * @brief Destructor for the MyGame class.
     */
    ~Scene4();

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

    void switchFullscreenShader();

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds

    // Initialize all VBOs here
    MeshEntity* m_ship = nullptr; //Pointer to the ship entity
    InstancedMeshEntity* m_instanceMines = nullptr; //Pointer to the instanced tree entity
    MyPlayer* m_player = nullptr; //Pointer to the player entity
    QuadEntity* m_button = nullptr; //Pointer to the button entity

    float m_uiScaleX = 2.0; //UI scale factor for the x-axis
    float m_uiScaleY = -2.0; //UI scale factor for the y-axis

    //shader stuff
    vector<ShaderPtr> m_fullScreenShaders;
    uint currentIndex = -1;

    Texture2DPtr m_oldRipple = nullptr;
    Texture2DPtr m_grayNoiseSmall = nullptr;
};