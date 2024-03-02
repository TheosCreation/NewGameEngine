#include "Game.h"
#include "VertexArrayObject.h"
#include "UniformBuffer.h"
#include "ShaderProgram.h"

struct UniformData
{
    float scale;
};

Game::Game()
{
    //init GLFW ver 4.6
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //init window
    Window = glfwCreateWindow(1000, 1000, "First OpenGL Window", NULL, NULL);
    if (Window == NULL)
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");

        onQuit();
    }
    glfwMakeContextCurrent(Window);

    //init GLEW
    if (glewInit() != GLEW_OK)
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");

        onQuit();
    }

    m_graphicsEngine->SetViewport(Rect(0, 0, 1000, 1000));
}

Game::~Game()
{
}

void Game::onCreate()
{
    //m_graphicsEngine->clear(Vec4(0,1,0,1));
    const float Vertices_Tri0[] = { // First triangle (top-left, bottom-left, bottom-right)
        -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f, 
        -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
    };  
    
    const float Vertices_Polygon0[] = {
        -0.8f, -0.8f, 0.0f,  1.0f, 0.0f, 0.0f, 
        -0.8f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.8f, 0.8f, 0.0f,  0.0f, 1.0f, 0.0f,
    };    

    VertexAttribute attribsList[] =
    {
        3, //Position
        3 //Color
    };

    m_polygonVAO = m_graphicsEngine->createVertexArrayObject({
        (void*)Vertices_Polygon0,
        sizeof(float) * (3+3),
        4,                          // number of vertices

        attribsList,
        2
        });

    m_uniform = m_graphicsEngine->createUniform({
        sizeof(UniformData)
        });

    m_shader = m_graphicsEngine->createShaderProgram({ 
            L"BasicShader",
            L"BasicShader"
        });

    m_shader->setUniformBufferSlot("UniformData", 0);
}

void Game::onUpdate()
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


    // applying deltaTime to data
    m_scale += 0.707f * deltaTime;
    auto currentScale = abs(sin(m_scale));


    // passing data into shaders using uniform
    UniformData data = { currentScale };
    m_uniform->setData(&data);


    m_graphicsEngine->clear(Vec4(0, 0, 0, 1));

    glfwPollEvents();

    m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
    m_graphicsEngine->setUniformBuffer(m_uniform, 0);
    m_graphicsEngine->setShaderProgram(m_shader);

    m_graphicsEngine->drawTriangles(TriangleStrip, m_polygonVAO->getVertexBufferSize(), 0);
}

void Game::onQuit()
{
    quit();
}

void Game::run()
{
	onCreate();

    //run funcs while window open
    while (glfwWindowShouldClose(Window) == false)
    {
        onUpdate();

        m_graphicsEngine->Render(Window);
    }

    onQuit();
}

void Game::quit()
{
    glfwTerminate();
}



