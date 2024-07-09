/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : MyPlayer.h
Description : MyPlayer class is an entity that can be adjusted by the end user
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"
#include "InstancedMeshEntity.h"
#include "QuadEntity.h"

/**
 * @class MyPlayer
 * @brief An entity that can be adjusted by the end user.
 */
class MyPlayer : public Entity
{
public:
    /**
     * @brief Constructor for the MyPlayer class.
     */
    MyPlayer();

    /**
     * @brief Destructor for the MyPlayer class.
     */
    ~MyPlayer();

    /**
     * @brief Called when the player entity is created.
     */
    virtual void onCreate();

    /**
     * @brief Called every frame to update the player entity.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onUpdate(float deltaTime);

    /**
     * @brief Called every frame after all Update functions have been called.
     * Can be overridden by derived classes to implement custom behavior.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void onLateUpdate(float deltaTime);

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds
    Entity* m_entity = nullptr; //Pointer to the entity
    
    float m_movementSpeed = 50.0f; //Movement speed of the movable object
    float m_originalMovementSpeed = m_movementSpeed; //Original movement speed
    float m_yaw = 0.0f; //Yaw angle for rotation of the camera
    float m_pitch = 0.0f; //Pitch angle for rotation of the camera
    float m_minFov = 1.0f; //Minimum fov for the camera
    float m_fov = 90.0f; //Fov for the camera
    float m_maxFov = 120.0f; //Maximum fov for the camera
    float m_zoomSpeed = 0.5f; //Speed of zooming
    bool m_playMode = false; //Flag for play mode
    bool m_wireframeMode = false; //Flag for wireframe mode

    Camera* m_cam = nullptr; //Pointer to the main camera
    Camera* m_uiCamera = nullptr; //Pointer to the UI camera
    InputManager* input = nullptr; //Pointer to the input manager
    LightManager* lighting = nullptr; //Pointer to the light manager
};