/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Game.cpp
Description : Game class that controls the order the graphics engine and internal systems performs tasks
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Game.h"
#include "Window.h"
#include "VertexArrayObject.h"
#include "Shader.h"
#include "EntitySystem.h"
#include "GraphicsEntity.h"
#include "Camera.h"
#include "SkyBoxEntity.h"
#include <glew.h>
#include <glfw3.h>

Game::Game()
{
    //init GLFW ver 4.6
    if (!glfwInit())
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");
        return;
    }

    initRandomSeed();
    m_display = std::make_unique<Window>();

    m_resourceManager = std::make_unique<ResourceManager>(this);
    m_graphicsEngine = std::make_unique<GraphicsEngine>();
    m_graphicsEngine->setViewport(m_display->getInnerSize());
    m_graphicsEngine->setDepthFunc(DepthType::Less);
    m_graphicsEngine->setBlendFunc(BlendType::SrcAlpha, BlendType::OneMinusSrcAlpha);
    m_graphicsEngine->setFaceCulling(CullType::BackFace);
    m_graphicsEngine->setWindingOrder(WindingOrder::CounterClockWise);
    //m_graphicsEngine->setScissorSize(Rect(200, 200, 400, 300));
    m_graphicsEngine->setMultiSampling(true);
    

    m_entitySystem = std::make_unique<EntitySystem>(this);

    m_inputManager = std::make_unique<InputManager>();
    m_inputManager->setGameWindow(m_display->getWindow());
    m_inputManager->setScreenArea(m_display->getInnerSize());

    m_lightManager = std::make_unique<LightManager>();

    //Creating skybox object
    m_skyBox = std::make_unique<SkyboxEntity>();
}

Game::~Game()
{
}

void Game::onCreate()
{
    m_sphereMesh = getResourceManager()->createMeshFromFile("Resources/Meshes/sphere.obj");
    m_cubeMesh = getResourceManager()->createMeshFromFile("Resources/Meshes/cube.obj");

    ShaderPtr skyboxShader = m_graphicsEngine->createShader({
            L"SkyBoxShader",
            L"SkyBoxShader"
        });

    m_skyBox->setEntitySystem(m_entitySystem.get());
    m_skyBox->setMesh(m_cubeMesh);
    m_skyBox->setShader(skyboxShader);
}

void Game::onCreateLate()
{
    auto camId = typeid(Camera).hash_code();

    auto it = m_entitySystem->m_entities.find(camId);

    if (it != m_entitySystem->m_entities.end())
    {
        for (auto& [key, camera] : it->second)
        {
            auto cam = dynamic_cast<Camera*>(camera.get());
            if (cam)
            {
                // Set the screen area for all cameras
                cam->setScreenArea(m_display->getInnerSize());
            }
        }
    }
}

void Game::onUpdateInternal()
{
    m_inputManager->onUpdate();

    // delta time
    m_currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = m_currentTime - m_previousTime;
    m_previousTime = m_currentTime;

    m_entitySystem->onUpdate(deltaTime);
    // Accumulate time
    m_accumulatedTime += deltaTime;

    // Perform fixed updates
    while (m_accumulatedTime >= m_fixedTimeStep)
    {
        onFixedUpdate();
        m_entitySystem->onFixedUpdate();
        m_accumulatedTime -= m_fixedTimeStep;
    }

    onUpdate(deltaTime);

    m_inputManager->onLateUpdate();

    onLateUpdate(deltaTime);

    double RenderTime_Begin = (double)glfwGetTime();
    onGraphicsUpdate(deltaTime);
    double RenderTime_End = (double)glfwGetTime();
}

void Game::onGraphicsUpdate(float deltaTime)
{
    m_graphicsEngine->clear(glm::vec4(0, 0, 0, 1));
    UniformData data = {};

    auto camId = typeid(Camera).hash_code();

    auto it = m_entitySystem->m_entities.find(camId);

    if (it != m_entitySystem->m_entities.end())
    {
        for (auto& [key, camera] : it->second)
        {
            auto cam = dynamic_cast<Camera*>(camera.get());
            if (cam && cam->getCameraType() == CameraType::Perspective)
            {
                // First camera should be game camera
                cam->getViewMatrix(data.viewMatrix);
                cam->getProjectionMatrix(data.projectionMatrix);
                data.cameraPosition = cam->getPosition();
                m_lightManager->setSpotlightPosition(data.cameraPosition);
                m_lightManager->setSpotlightDirection(cam->getForwardDirection());
                
            }
            else if(cam)
            {
                // Second camera which should be UI camera
                cam->getViewMatrix(data.uiViewMatrix);
                cam->getProjectionMatrix(data.uiProjectionMatrix);
            }
        }
    }
    data.currentTime = m_currentTime;

    // Render skybox
    ShaderPtr skyboxShader = m_skyBox->getShader();
    m_graphicsEngine->setShader(skyboxShader);
    m_skyBox->setUniformData(data);
    m_skyBox->onGraphicsUpdate(deltaTime);

    //m_graphicsEngine->setScissor(true);
    //m_graphicsEngine->setStencil(StencilOperationType::Set);
    //m_graphicsEngine->setStencil(StencilOperationType::ResetAlways);
    
    ShaderPtr currentShader = nullptr;
    for (auto& [key, entities] : m_entitySystem->m_entities)
    {
        // For each graphics entity
        for (auto& [key, entity] : entities)
        {
            auto e = dynamic_cast<GraphicsEntity*>(entity.get());
            if (e)
            {
                ShaderPtr shader = e->getShader();
                if (shader != currentShader)
                {
                    // Set the shader only if it is different from the current one
                    m_graphicsEngine->setShader(shader);
                    // Apply lighting to the shader
                    m_lightManager->applyLighting(shader);
                    currentShader = shader;
                }
                // Apply other uniform data to the shader
                e->setUniformData(data);

                e->onGraphicsUpdate(deltaTime);
            }
            else
            {
                break;
            }
        }
    }
    
    //m_graphicsEngine->setStencil(StencilOperationType::ResetNotEqual);
    //
    //for (auto& [key, entities] : m_entitySystem->m_entities)
    //{
    //    // For each graphics entity
    //    for (auto& [key, entity] : entities)
    //    {
    //        auto e = dynamic_cast<GraphicsEntity*>(entity.get());
    //        if (e)
    //        {
    //            ShaderPtr shader = e->getShader();
    //            if (shader != currentShader)
    //            {
    //                // Set the shader only if it is different from the current one
    //                m_graphicsEngine->setShader(shader);
    //                // Apply lighting to the shader
    //                m_lightManager->applyLighting(shader);
    //                currentShader = shader;
    //            }
    //
    //            // Apply other uniform data to the shader
    //            e->setUniformData(data);
    //            e->onGraphicsUpdate(deltaTime);
    //        }
    //        else
    //        {
    //            break;
    //        }
    //    }
    //}
    //m_graphicsEngine->setStencil(StencilOperationType::ResetAlways);

    // Render to window
    m_display->present();
}

void Game::onLateUpdate(float deltaTime)
{
    for (auto& [key, entities] : m_entitySystem->m_entities)
    {
        for (auto& [key, entity] : entities)
        {
            entity->onLateUpdate(deltaTime);
        }
    }
}

void Game::onQuit()
{
    quit();
}

void Game::run()
{
	onCreate();
	onCreateLate();

    //run funcs while window open
    while (m_display->shouldClose() == false)
    {
        glfwPollEvents();
        onUpdateInternal();
    }

    onQuit();
}

void Game::quit()
{
    m_display.release();
}

EntitySystem* Game::getEntitySystem()
{
    return m_entitySystem.get();
}

GraphicsEngine* Game::getGraphicsEngine()
{
    return m_graphicsEngine.get();
}

InputManager* Game::getInputManager()
{
    return m_inputManager.get();
}

LightManager* Game::getLightingManager()
{
    return m_lightManager.get();
}

TexturePtr Game::getSkyboxTexture()
{
    return m_skyBox->getTexture();
}

ResourceManager* Game::getResourceManager()
{
    return m_resourceManager.get();
}

Window* Game::getWindow()
{
    return m_display.get();
}