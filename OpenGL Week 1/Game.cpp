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
#include "TextureCubeMap.h"
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

    // create a cube map texture and set the texture of the skybox to the cubemap texture
    std::vector<std::string> skyboxCubeMapTextureFilePaths;
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Right.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Left.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Top.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Bottom.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Back.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Front.png");
    TextureCubeMapPtr skyBoxTexture = resourceManager.createCubeMapTextureFromFile(skyboxCubeMapTextureFilePaths);
    m_skyBox->setTexture(skyBoxTexture);
}

void Game::onCreateLate()
{
    for (auto& camera : m_entitySystem->getCameras())
    {
        // Set the screen area for all cameras
        camera->setScreenArea(m_display->getInnerSize());
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
    data.currentTime = m_currentTime;
    for (auto& camera : m_entitySystem->getCameras())
    {
        if(camera->getCameraType() == CameraType::Perspective)
		{
			camera->getViewMatrix(data.viewMatrix);
			camera->getProjectionMatrix(data.projectionMatrix);
			data.cameraPosition = camera->getPosition();
			lightManager.setSpotlightPosition(data.cameraPosition);
			lightManager.setSpotlightDirection(camera->getForwardDirection());
		}
		else
		{
			camera->getViewMatrix(data.uiViewMatrix);
			camera->getProjectionMatrix(data.uiProjectionMatrix);
		}
    }

    // Render skybox
    ShaderPtr skyboxShader = m_skyBox->getShader();
    graphicsEngine.setShader(skyboxShader);
    m_skyBox->setUniformData(data);
    m_skyBox->onGraphicsUpdate(deltaTime);

    //graphicsEngine.setScissor(true);
    //m_graphicsEngine->setStencil(StencilOperationType::Set);
    //m_graphicsEngine->setStencil(StencilOperationType::ResetAlways);
    
    ShaderPtr currentShader = nullptr;
    for (auto& graphicsEntity : m_entitySystem->getGraphicsEntities())
    {
        ShaderPtr shader = graphicsEntity->getShader();
        if (shader != currentShader)
        {
            // Set the shader only if it is different from the current one
            graphicsEngine.setShader(shader);
            // Apply lighting to the shader
            lightManager.applyLighting(shader);
            currentShader = shader;
        }
        // Apply other uniform data to the shader
        graphicsEntity->setUniformData(data);

        graphicsEntity->onGraphicsUpdate(deltaTime);
    }

    //graphicsEngine.setScissor(false);
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

    //graphicsEngine.setScissor(false);
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