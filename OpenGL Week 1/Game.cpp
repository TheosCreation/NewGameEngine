#include "Game.h"
#include "Window.h"
#include "VertexArrayObject.h"
#include "UniformBuffer.h"
#include "ShaderProgram.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Vec2.h"
#include "EntitySystem.h"
#include "GraphicsEntity.h"
#include "Camera.h"

struct UniformData
{
    Mat4 world;
    Mat4 view;
    Mat4 projection;
};

struct Vertex
{
    Vec3 position;
    Vec2 texcoord;
};

Game::Game()
{
    //init GLFW ver 4.6
    glfwInit();

    m_display = std::make_unique<Window>();
    m_graphicsEngine = std::make_unique<GraphicsEngine>();
    m_entitySystem = std::make_unique<EntitySystem>();
    m_inputManager = std::make_unique<InputManager>();

    m_inputManager->SetGameWindow(m_display->getWindow());
    m_display->makeCurrentContext();

    m_graphicsEngine->SetViewport(m_display->getInnerSize());
    m_graphicsEngine->setFaceCulling(CullType::BackFace);
    m_graphicsEngine->setWindingOrder(WindingOrder::ClockWise);

    getInputManager()->setScreenArea(m_display->getInnerSize());
    //m_uniform = m_graphicsEngine->createUniform({
    //    sizeof(UniformData)
    //});
    //
    //m_shader = m_graphicsEngine->createShaderProgram({
    //        L"BasicShader",
    //        L"BasicShader"
    //});
    //
    //m_shader->setUniformBufferSlot("UniformData", 0);
}

Game::~Game()
{
}

void Game::onCreate()
{
    
}

void Game::onUpdateInternal()
{
    // delta time
    auto currentTime = std::chrono::system_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>();
    if (m_previousTime.time_since_epoch().count())
    {
        elapsedSeconds = currentTime - m_previousTime;
    }
    m_previousTime = currentTime;

    auto deltaTime = (float)elapsedSeconds.count();

    onUpdate(deltaTime);
    m_entitySystem->update(deltaTime);


    // applying deltaTime to data
    m_scale += 0.707f * deltaTime;
    auto currentScale = abs(sin(m_scale));

    Mat4 world, projection, temp;
    temp.setIdentity();
    temp.setScale(Vec3(1, 1, 1));
    world *= temp;

    temp.setIdentity();
    temp.setRotationX(m_scale);
    world *= temp;
    
    temp.setIdentity();
    temp.setRotationY(m_scale);
    world *= temp;
    
    temp.setIdentity();
    temp.setRotationZ(m_scale);
    world *= temp;
    
    Rect displaysize = m_display->getInnerSize();
    projection.setOrthoLH(displaysize.width * 0.004f, displaysize.height * 0.004f, 0.1f, 100.0f);

    // passing data into shaders using uniform
    UniformData data = { world , projection };
    m_uniform->setData(&data);
    
    onGraphicsUpdate(deltaTime);

    glfwPollEvents();

    //m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
    //m_graphicsEngine->setUniformBuffer(m_uniform, 0);

    //m_graphicsEngine->drawIndexedTriangles(TriangleType::TriangleList, 36);
}

void Game::onGraphicsUpdate(float deltaTime)
{
    m_graphicsEngine->clear(Vec4(0, 0, 0, 1));
    
    UniformData data = {};
    
    
    
    auto camId = typeid(Camera).hash_code();
    
    auto it = m_entitySystem->m_entities.find(camId);
    
    
    //let's set the camera data to the uniformdata structure, in order to pass them to the shaders for the final rendering
    if (it != m_entitySystem->m_entities.end())
    {
        for (auto& [key, camera] : it->second)
        {
            //the camera data are the view and projection
            //view is simply the world matrix of the camera inverted
            Mat4 w;
            auto cam = dynamic_cast<Camera*>(camera.get());
            cam->getViewMatrix(data.view);
            cam->setScreenArea(m_display->getInnerSize());
            cam->getProjectionMatrix(data.projection);
        }
    }
    
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
                m_graphicsEngine->setShaderProgram(m_shader); //bind shaders to graphics pipeline
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
        onUpdateInternal();
    }

    onQuit();
}

void Game::quit()
{
    glfwTerminate();
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

Window* Game::getWindow()
{
    return m_display.get();
}



