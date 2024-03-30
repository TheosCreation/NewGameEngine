#include "Game.h"
#include "Window.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"
#include "EntitySystem.h"
#include "GraphicsEntity.h"
#include "HexagonEntity.h"
#include "QuadEntity.h"
#include "Camera.h"
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

    
    m_display = std::make_unique<Window>();

    m_resourceManager = std::make_unique<ResourceManager>(this);
    m_graphicsEngine = std::make_unique<GraphicsEngine>();
    m_graphicsEngine->SetViewport(m_display->getInnerSize());
    m_graphicsEngine->setFaceCulling(CullType::BackFace);
    m_graphicsEngine->setWindingOrder(WindingOrder::ClockWise);

    m_entitySystem = std::make_unique<EntitySystem>(this);

    m_inputManager = std::make_unique<InputManager>();
    m_inputManager->SetGameWindow(m_display->getWindow());
    m_inputManager->setScreenArea(m_display->getInnerSize());

}

Game::~Game()
{
}

void Game::onCreate()
{
}

void Game::onUpdateInternal()
{
    m_inputManager->update();

    // delta time
    m_currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = m_currentTime - m_previousTime;
    m_previousTime = m_currentTime;

    m_entitySystem->update(deltaTime);

    onUpdate(deltaTime);
    
    onGraphicsUpdate(deltaTime);
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
            //the camera data are the view and projection
            auto cam = dynamic_cast<Camera*>(camera.get());
            //change this to calculate the mvp and pass in one matrix
            cam->getViewMatrix(data.view);
            cam->setScreenArea(m_display->getInnerSize());
            cam->getProjectionMatrix(data.projection);
            
        }
    }

    data.currentTime = m_currentTime;

    for (auto& [key, entities] : m_entitySystem->m_entities)
    {
        //for each graphics entity
        for (auto& [key, entity] : entities)
        {
            auto e = dynamic_cast<GraphicsEntity*>(entity.get());
            if (e)
            {
                //let's retrive the model matrix
                e->getModelMatrix(data.model);

                m_graphicsEngine->setShaderProgram(e->getShader());

                e->setUniformData(data);

                e->onGraphicsUpdate(deltaTime);
            }
            else
            {
                break;
            }
        }
    }
    // Render to window
    m_display->present();
}

void Game::onQuit()
{
    quit();
}

void Game::run()
{
	onCreate();

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

ResourceManager* Game::getResourceManager()
{
    return m_resourceManager.get();
}

Window* Game::getWindow()
{
    return m_display.get();
}



