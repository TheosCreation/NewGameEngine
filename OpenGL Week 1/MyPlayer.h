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
     * @brief Adds a reference to a button entity.
     * @param buttonRef Pointer to the button entity.
     */
    void addButtonRef(QuadEntity* buttonRef);

    /**
     * @brief Sets the textures for the button entity.
     * @param buttonUpTexture Texture for the button in the up state.
     * @param buttonHoveringTexture Texture for the button in the hovering state.
     * @param buttonDownTexture Texture for the button in the down state.
     */
    void setButtonTextures(TexturePtr buttonUpTexture, TexturePtr buttonHoveringTexture, TexturePtr buttonDownTexture);

    /**
     * @brief Sets the instanced entity and its textures.
     * @param instancedEntityRef Pointer to the instanced entity.
     * @param texture1 First texture for the instanced entity.
     * @param texture2 Second texture for the instanced entity.
     */
    void setInstancedEntity(InstancedMeshEntity* instancedEntityRef, TexturePtr texture1, TexturePtr texture2);

private:
    float m_elapsedSeconds = 0.0f; //Elapsed time in seconds
    Entity* m_entity = nullptr; //Pointer to the entity

    float m_movementSpeed = 50.0f; //Movement speed of the movable object
    float m_yaw = 0.0f;
    float m_pitch = 0.0f;
    float m_minFov = 1.0f;
    float m_fov = 90.0f;
    float m_maxFov = 120.0f;
    float m_zoomSpeed = 0.5f;
    glm::vec3 m_playerHeightOffset{0.0f, 40.0f, 0.0f}; //Height offset to position the camera
    bool m_playMode = false; //Flag for play mode
    bool m_wireframeMode = false; //Flag for wireframe mode

    Camera* m_cam = nullptr; //Pointer to the main camera
    Camera* m_uiCamera = nullptr; //Pointer to the UI camera
    InputManager* input = nullptr; //Pointer to the input manager
    LightManager* lighting = nullptr; //Pointer to the light manager

    std::vector<QuadEntity*> m_buttonRefs; //References to button entities
    InstancedMeshEntity* m_instancedEntity; //Pointer to the instanced entity
    TexturePtr m_instancedEntityTexture1Ptr; //First texture for the instanced entity
    TexturePtr m_instancedEntityTexture2Ptr; //Second texture for the instanced entity

    TexturePtr m_buttonUpTexture; //Texture for the button in the up state
    TexturePtr m_buttonHoveringTexture; //Texture for the button in the hovering state
    TexturePtr m_buttonDownTexture; //Texture for the button in the down state
    bool m_instancedTextureSwitched; //Flag for switching instanced textures
    bool m_buttonTextureSwitched; //Flag for switching button textures
};