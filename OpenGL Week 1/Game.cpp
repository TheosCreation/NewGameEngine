#include "Game.h"
#include "Window.h"
#include "VertexArrayObject.h"
#include "UniformBuffer.h"
#include "ShaderProgram.h"
#include "EntitySystem.h"
#include "GraphicsEntity.h"
#include "Camera.h"
#include <glew.h>
#include <glfw3.h>

struct UniformData
{
    glm::mat4 world;
    glm::mat4 view;
    glm::mat4 projection;
    float currentTime;
};

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
    

    m_uniform = m_graphicsEngine->createUniform({
        sizeof(UniformData)
    });
}

Game::~Game()
{
}

void Game::onCreate()
{
    //if orthogoanal camera then
    m_entitySystem->globalScale = 1.0f;
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
            //view is simply the world matrix of the camera inverted
            auto cam = dynamic_cast<Camera*>(camera.get());
            //change this to calculate the mvp and pass in one matrix
            cam->getViewMatrix(data.view);
            cam->setScreenArea(m_display->getInnerSize());
            cam->getProjectionMatrix(data.projection);
            
        }
    }

    // sets the current time
    data.currentTime = deltaTime;

    for (auto& [key, entities] : m_entitySystem->m_entities)
    {
        //for each graphics entity
        for (auto& [key, entity] : entities)
        {
            auto e = dynamic_cast<GraphicsEntity*>(entity.get());

            if (e)
            {
                //let's retrive the world matrix and let's pass it to the uniform buffer
                e->getWorldMatrix(data.world);

                m_uniform->setData(&data);
                m_graphicsEngine->setUniformBuffer(m_uniform, 0); // bind uniform buffer

                //call internal graphcis update of the entity in order to handle specific graphics data/functions 
                e->onGraphicsUpdate(deltaTime);
            }
            else
            {
                break;
            }
        }
    }
    // Render to window
    m_display->present(false);
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



