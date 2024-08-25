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
#include "MyScene.h"

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
    auto windowSize = m_display->getInnerSize();
    m_framebuffer = std::make_unique<Framebuffer>(windowSize);

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setViewport(windowSize);
    graphicsEngine.setDepthFunc(DepthType::Less);
    graphicsEngine.setBlendFunc(BlendType::SrcAlpha, BlendType::OneMinusSrcAlpha);
    graphicsEngine.setFaceCulling(CullType::BackFace);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setScissorSize(Rect(200, 200, 400, 300));
    graphicsEngine.setMultiSampling(true);

    auto& inputManger = InputManager::GetInstance();
    inputManger.setGameWindow(m_display->getWindow());
    inputManger.setScreenArea(windowSize);

}

Game::~Game()
{
}

void Game::onCreate()
{
    auto& resourceManager = ResourceManager::GetInstance();
    m_sphereMesh = resourceManager.createMeshFromFile("Resources/Meshes/sphere.obj");
    m_cubeMesh = resourceManager.createMeshFromFile("Resources/Meshes/cube.obj");

    auto scene = std::make_shared<MyScene>(this);
    SetScene(scene);

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    ShaderPtr quadShader = graphicsEngine.createShader({
            L"QuadShader",
            L"QuadShader"
        });
    m_canvasQuad = std::make_unique<QuadEntity>();
    m_canvasQuad->onCreate();
    m_canvasQuad->setShader(quadShader);
    Texture2DPtr sciFiSpace = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
    //m_canvasQuad->setTexture(getFrameBufferRenderTexureId());
    m_canvasQuad->setTexture(sciFiSpace->getId());
    //m_canvasQuad->setColor(Color::Red);
}

void Game::onCreateLate()
{
    m_currentScene->onCreateLate();
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

    m_currentScene->onUpdate(deltaTime);
    m_canvasQuad->onUpdate(deltaTime);

    if (inputManager.isKeyPressed(Key::Key1))
    {
        auto scene = std::make_shared<MyScene>(this);
        SetScene(scene);
    }
    // Perform fixed updates
    while (m_accumulatedTime >= m_fixedTimeStep)
    {
        float fixedDeltaTime = m_currentTime - m_previousFixedUpdateTime;
        m_previousFixedUpdateTime = m_currentTime;
        m_currentScene->onFixedUpdate(fixedDeltaTime);
        m_canvasQuad->onFixedUpdate(fixedDeltaTime);
        m_accumulatedTime -= m_fixedTimeStep;
    }

    m_currentScene->onLateUpdate(deltaTime);
    m_canvasQuad->onLateUpdate(deltaTime);
    inputManager.onLateUpdate();

    double RenderTime_Begin = (double)glfwGetTime();
    //m_framebuffer->Bind();
    m_currentScene->onGraphicsUpdate(deltaTime);
    //m_framebuffer->UnBind();
    ShaderPtr shader = m_canvasQuad->getShader();
    GraphicsEngine::GetInstance().setShader(shader);
    m_canvasQuad->onGraphicsUpdate(deltaTime);
    double RenderTime_End = (double)glfwGetTime();

    // Render to window
    m_display->present();
}

void Game::onQuit()
{
    m_currentScene->onQuit();
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

void Game::SetScene(shared_ptr<Scene> _scene)
{
    // if there is a current scene, call onQuit
    if (m_currentScene != nullptr)
    {
        m_currentScene->onQuit();
        LightManager::GetInstance().clearLights(); 
        ResourceManager::GetInstance().ClearInstancesFromMeshes();
    }
    // set the current scene to the new scene
    m_currentScene = _scene;
    m_currentScene->onCreate();
    m_currentScene->onCreateLate();
}

Window* Game::getWindow()
{
    return m_display.get();
}

float Game::GetCurrentTime()
{
    return m_currentTime;
}

MeshPtr Game::getCubeMesh()
{
    return m_cubeMesh;
}

MeshPtr Game::getSphereMesh()
{
    return m_sphereMesh;
}

uint Game::getFrameBufferRenderTexureId()
{
    return m_framebuffer->RenderTexture;
}
