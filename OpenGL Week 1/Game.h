/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Game.h
Description : Game class that controls the order the graphics engine and internal systems performs tasks
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <iostream>
#include "InputManager.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "LightManager.h"

// Forward declarations of classes
class Window;
class EntitySystem;
class SkyboxEntity;

/**
 * @class Game
 * @brief Controls the order in which the graphics engine and internal systems performs tasks.
 */
class Game
{
public:
    /**
     * @brief Constructor for the Game class.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /**
     * @brief Runs the game loop.
     */
    void run();

    /**
     * @brief Quits the game.
     */
    void quit();

    /**
     * @brief Gets the EntitySystem instance.
     * @return A pointer to the EntitySystem instance.
     */
    EntitySystem* getEntitySystem();

    /**
     * @brief Gets the GraphicsEngine instance.
     * @return A pointer to the GraphicsEngine instance.
     */
    GraphicsEngine* getGraphicsEngine();

    /**
     * @brief Gets the InputManager instance.
     * @return A pointer to the InputManager instance.
     */
    InputManager* getInputManager();

    LightManager* getLightingManager();

    TexturePtr getSkyboxTexture();

    /**
     * @brief Gets the ResourceManager instance.
     * @return A pointer to the ResourceManager instance.
     */
    ResourceManager* getResourceManager();

    /**
     * @brief Gets the Window instance.
     * @return A pointer to the Window instance.
     */
    Window* getWindow();

protected:
    /**
     * @brief Called when the game is created.
     */
    virtual void onCreate();

    /**
     * @brief Called when the game and after onCreate.
     */
    virtual void onCreateLate();

    /**
     * @brief Called every frame to update the game logic.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onUpdate(float deltaTime) {};

    /**
     * @brief Called every frame to update the entity at a fixed frame rate.
     * Can be overridden by derived classes to implement custom behavior.
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void onFixedUpdate() {};

    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(float deltaTime);

    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onLateUpdate(float deltaTime);

    /**
     * @brief Called when the game is quitting.
     */
    virtual void onQuit();

private:
    /**
     * @brief Internal function to update the game.
     */
    void onUpdateInternal();

protected:
    bool m_isRunning = true; //Indicates whether the game is running
    std::unique_ptr<Window> m_display; //Pointer to the window instance
    std::unique_ptr<InputManager> m_inputManager; //Pointer to the input manager instance
    std::unique_ptr<GraphicsEngine> m_graphicsEngine; //Pointer to the graphics engine instance
    std::unique_ptr<EntitySystem> m_entitySystem; //Pointer to the entity system instance
    std::unique_ptr<ResourceManager> m_resourceManager; //Pointer to the resource manager instance
    std::unique_ptr<LightManager> m_lightManager; //Pointer to the resource manager instance
    std::unique_ptr<SkyboxEntity> m_skyBox; //Pointer to the sky box instance

    float m_previousTime = 0; //The previous frame's time
    float m_currentTime = 0; //The current frame's time
    const float m_fixedTimeStep = 1.0f / 60.0f; // Fixed time step (60 FPS)
    float m_accumulatedTime = 0; //The current frame's time
    float m_scale = 0; //The scale factor for time

    //collection of useful meshes
    MeshPtr m_cubeMesh;
    MeshPtr m_sphereMesh;
};