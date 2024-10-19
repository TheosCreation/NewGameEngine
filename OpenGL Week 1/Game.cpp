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
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Framebuffer.h"
#include "GeometryBuffer.h"
#include "SSRQuad.h"

Game::Game()
{
    //init GLFW ver 4.6
    if (!glfwInit())
    {
        Debug::LogError("GLFW failed to initialize properly. Terminating program.");
        return;
    }

    initRandomSeed();
    m_display = std::make_unique<Window>(this);

    Vector2 windowSize = m_display->getInnerSize();
    m_postProcessingFramebuffer = std::make_unique<Framebuffer>(windowSize);
    GeometryBuffer::GetInstance().Init(windowSize);
    m_shadowMap = std::make_unique<ShadowMap>(Vector2(4096.0f));

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
    

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    defaultQuadShader = graphicsEngine.createShader({
            "ScreenQuad",
            "QuadShader"
        });
    ssrQuadShader = graphicsEngine.createShader({
            "ScreenQuad",
            "SSRShader"
        });

    m_SSRQuad = std::make_unique<SSRQuad>();
    m_SSRQuad->onCreate();
    m_SSRQuad->setShader(ssrQuadShader);

    m_canvasQuad = std::make_unique<QuadEntity>();
    m_canvasQuad->onCreate();
    m_canvasQuad->setTextureFromId(m_postProcessingFramebuffer->RenderTexture);
    m_canvasQuad->setShader(defaultQuadShader);

    auto scene1 = std::make_shared<Scene1>(this);
    SetScene(scene1);
}

void Game::onCreateLate()
{
    m_currentScene->onCreateLate();
}

void Game::onUpdateInternal()
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    auto& inputManager = InputManager::GetInstance();
    inputManager.onUpdate();

    // delta time
    m_currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = m_currentTime - m_previousTime;
    m_previousTime = m_currentTime;

    // Accumulate time
    m_accumulatedTime += deltaTime;

    m_currentScene->onUpdate(deltaTime);

    if (inputManager.isKeyPressed(Key::Key1))
    {
        auto scene1 = std::make_shared<Scene1>(this);
        SetScene(scene1);
    }
    
    if (inputManager.isKeyPressed(Key::Key2))
    {
        auto scene2 = std::make_shared<Scene2>(this);
        SetScene(scene2);
    }
    
    if (inputManager.isKeyPressed(Key::Key3))
    {
        auto scene3 = std::make_shared<Scene3>(this);
        SetScene(scene3);
    }
    
    if (inputManager.isKeyPressed(Key::Key4))
    {
        auto scene4 = std::make_shared<Scene4>(this);
        SetScene(scene4);
    }
    // Perform fixed updates
    while (m_accumulatedTime >= m_fixedTimeStep)
    {
        float fixedDeltaTime = m_currentTime - m_previousFixedUpdateTime;
        m_previousFixedUpdateTime = m_currentTime;
        m_currentScene->onFixedUpdate(fixedDeltaTime);
        m_accumulatedTime -= m_fixedTimeStep;
    }

    m_currentScene->onLateUpdate(deltaTime);
    inputManager.onLateUpdate();

    double RenderTime_Begin = (double)glfwGetTime();

    graphicsEngine.clear(glm::vec4(0, 0, 0, 1)); //clear the existing stuff first is a must

    //Geometry Pass

    auto& geometryBuffer = GeometryBuffer::GetInstance();
    geometryBuffer.Bind();
    graphicsEngine.clear(glm::vec4(0, 0, 0, 1));
    m_currentScene->onGeometryPass();
    geometryBuffer.UnBind();


    m_SSRQuad->onGraphicsUpdate(UniformData{});
    geometryBuffer.WriteDepth();

    //Shadow Pass
    m_shadowMap->Bind();
    m_currentScene->onShadowPass();
    m_shadowMap->UnBind();
    //
    //LightManager::GetInstance().setShadowMapTexture(m_shadowMap);

    //m_postProcessingFramebuffer->Bind();
    //graphicsEngine.clear(glm::vec4(0, 0, 0, 1));

    //m_currentScene->onGraphicsUpdate(deltaTime);

    //m_postProcessingFramebuffer->UnBind();


    //graphicsEngine.clear(glm::vec4(0, 0, 0, 1)); //clear the scene
    //NewUniformData uniformData;
    //uniformData.CreateData<float>("Time", m_currentTime);
    //uniformData.CreateData<Vector2>("Resolution", m_display->getInnerSize());
    //if (currentTexture1)
    //{
    //    //if the current shader needs a second texture we pass that into it
    //    NewExtraTextureData textureData;
    //    textureData.AddTexture("Texture1", currentTexture1, 1);
    //    m_canvasQuad->onGraphicsUpdate(uniformData, textureData);
    //}
    //else
    //{
    //    m_canvasQuad->onGraphicsUpdate(uniformData);
    //}

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

void Game::onResize(int _width, int _height)
{
    m_currentScene->onResize(_width, _height);
    m_postProcessingFramebuffer->resize(Vector2(_width, _height));
    GeometryBuffer::GetInstance().Resize(Vector2(_width, _height));
    GraphicsEngine::GetInstance().setViewport(Vector2(_width, _height));
}

void Game::SetScene(shared_ptr<Scene> _scene)
{
    // if there is a current scene, call onQuit
    if (m_currentScene != nullptr)
    {
        m_currentScene->onQuit();
        LightManager::GetInstance().reset(); 
        ResourceManager::GetInstance().ClearInstancesFromMeshes();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    // set the current scene to the new scene
    m_currentScene = std::move(_scene);
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
void Game::SetFullScreenShader(ShaderPtr _shader, Texture2DPtr _texture)
{
    if (_shader == nullptr)
    {
        m_canvasQuad->setShader(defaultQuadShader);
    }
    else
    {
        m_canvasQuad->setShader(_shader);
    }
    currentTexture1 = _texture;
}