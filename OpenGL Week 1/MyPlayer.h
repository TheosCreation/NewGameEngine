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
     * @brief Sets the camera position.
     * @param newPosition The new position of the camera.
     */
    void setCameraPosition(glm::vec3 newPosition);

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

    glm::vec3 m_camPosition{}; //Camera position

    float m_movementSpeed = 50.0f; //Movement speed of the movable object
    float m_rotationSpeed = 5.0f; //Speed of the orbiting camera
    float m_zoomSpeed = 20.0f; //Speed the camera shortens or lengthens the orbit radius

    float m_originalOrbitSpeed = 5.0f; //Original orbit speed
    float m_orbitSpeed = m_originalOrbitSpeed; //Current orbit speed
    float m_orbitHorizontal = 0.0f; //Horizontal orbit angle
    float m_minimumOrbitalRadius = 35.0f; //Minimum orbital radius
    float m_maximumOrbitalRadius = 500.0f; //Maximum orbital radius
    float m_orbitRadius = 40.0f; //Current orbital radius
    float m_inactivityTimer = 1.0f; //Timer for inactivity

    bool m_autoRotate = false; //Flag for auto-rotation
    bool m_playMode = false; //Flag for play mode
    bool m_wireframeMode = false; //Flag for wireframe mode

    Camera* m_cam = nullptr; //Pointer to the main camera
    Camera* m_uiCamera = nullptr; //Pointer to the UI camera
    InputManager* input = nullptr; //Pointer to the input manager

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