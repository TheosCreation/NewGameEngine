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

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setViewport(m_display->getInnerSize());
    graphicsEngine.setDepthFunc(DepthType::Less);
    graphicsEngine.setBlendFunc(BlendType::SrcAlpha, BlendType::OneMinusSrcAlpha);
    graphicsEngine.setFaceCulling(CullType::BackFace);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setScissorSize(Rect(200, 200, 400, 300));
    graphicsEngine.setMultiSampling(true);
    

    m_entitySystem = std::make_unique<EntitySystem>(this);

    auto& inputManger = InputManager::GetInstance();
    inputManger.setGameWindow(m_display->getWindow());
    inputManger.setScreenArea(m_display->getInnerSize());

    //Creating skybox object
    m_skyBox = std::make_unique<SkyboxEntity>();
}

Game::~Game()
{
}

void Game::onCreate()
{
    auto& resourceManager = ResourceManager::GetInstance();
    m_sphereMesh = resourceManager.createMeshFromFile("Resources/Meshes/sphere.obj");
    m_cubeMesh = resourceManager.createMeshFromFile("Resources/Meshes/cube.obj");

    ShaderPtr skyboxShader = GraphicsEngine::GetInstance().createShader({
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
    auto& inputManager = InputManager::GetInstance();
    inputManager.onUpdate();

    // delta time
    m_currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = m_currentTime - m_previousTime;
    m_previousTime = m_currentTime;

    // Accumulate time
    m_accumulatedTime += deltaTime;

    onUpdate(deltaTime);
    m_entitySystem->onUpdate(deltaTime);

    // Perform fixed updates
    while (m_accumulatedTime >= m_fixedTimeStep)
    {
        float fixedDeltaTime = m_currentTime - m_previousFixedUpdateTime;
        m_previousFixedUpdateTime = m_currentTime;
        onFixedUpdate(fixedDeltaTime);
        m_entitySystem->onFixedUpdate(fixedDeltaTime);
        m_accumulatedTime -= m_fixedTimeStep;
    }

    onLateUpdate(deltaTime);

    m_entitySystem->onLateUpdate(deltaTime);

    inputManager.onLateUpdate();

    double RenderTime_Begin = (double)glfwGetTime();
    onGraphicsUpdate(deltaTime);
    double RenderTime_End = (double)glfwGetTime();
}

void Game::onGraphicsUpdate(float deltaTime)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    auto& lightManager = LightManager::GetInstance();

    graphicsEngine.clear(glm::vec4(0, 0, 0, 1));
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
                lightManager.setSpotlightPosition(data.cameraPosition);
                lightManager.setSpotlightDirection(cam->getForwardDirection());
                
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
    graphicsEngine.setShader(skyboxShader);
    m_skyBox->setUniformData(data);
    m_skyBox->onGraphicsUpdate(deltaTime);

    graphicsEngine.setScissor(true);
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
                    graphicsEngine.setShader(shader);
                    // Apply lighting to the shader
                    lightManager.applyLighting(shader);
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
    graphicsEngine.setScissor(false);
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

    graphicsEngine.setScissor(false);
    // Render to window
    m_display->present();
}

void Game::onLateUpdate(float deltaTime)
{
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

Window* Game::getWindow()
{
    return m_display.get();
}