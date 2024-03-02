#include "Game.h"
#include "VertexArrayObject.h"
#include "UniformBuffer.h"
#include "ShaderProgram.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Vec2.h"

struct UniformData
{
    Mat4 world;
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //init window
    Window = glfwCreateWindow(displaySize.width, displaySize.height, "First OpenGL Window", NULL, NULL);
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

    m_graphicsEngine->SetViewport(Rect(0, 0, displaySize.width, displaySize.height));
}

Game::~Game()
{
}

void Game::onCreate()
{
    Vec3 positionsList[] =
    {
        //front face
        Vec3(-0.5f, -0.5f, -0.5f),
        Vec3(-0.5f, 0.5f, -0.5f),
        Vec3(0.5f, 0.5f, -0.5f),
        Vec3(0.5f, -0.5f, -0.5f),

        //back face
        Vec3(0.5f, -0.5f, 0.5f),
        Vec3(0.5f, 0.5f, 0.5f),
        Vec3(-0.5f, 0.5f, 0.5f),
        Vec3(-0.5f, -0.5f, 0.5f)
    }; 
    
    Vec2 texcoordsList[] =
    {
           //U      V
        Vec2(0,     0.5),
        Vec2(0.5,   1),
        Vec2(1,     0.5),
        Vec2(1,     1)
    };

    Vertex verticesList[] =
    {
        //front face
        { positionsList[0],texcoordsList[1] },
        { positionsList[1],texcoordsList[0] },
        { positionsList[2],texcoordsList[2] },
        { positionsList[3],texcoordsList[3] },

        //back face
        { positionsList[4],texcoordsList[1] },
        { positionsList[5],texcoordsList[0] },
        { positionsList[6],texcoordsList[2] },
        { positionsList[7],texcoordsList[3] },

        //top face
        { positionsList[1],texcoordsList[1] },
        { positionsList[6],texcoordsList[0] },
        { positionsList[5],texcoordsList[2] },
        { positionsList[2],texcoordsList[3] },

        //bottom face
        { positionsList[7],texcoordsList[1] },
        { positionsList[0],texcoordsList[0] },
        { positionsList[3],texcoordsList[2] },
        { positionsList[4],texcoordsList[3] },

        //right face
        { positionsList[3],texcoordsList[1] },
        { positionsList[2],texcoordsList[0] },
        { positionsList[5],texcoordsList[2] },
        { positionsList[4],texcoordsList[3] },

        //left face
        { positionsList[7],texcoordsList[1] },
        { positionsList[6],texcoordsList[0] },
        { positionsList[1],texcoordsList[2] },
        { positionsList[0],texcoordsList[3] }
    };


    uint indicesList[] =
    {
        //front
        0,1,2,
        2,3,0,

        //back
        4,5,6,
        6,7,4,

        //top
        8,9,10,
        10,11,8,

        //bottom
        12,13,14,
        14,15,12,

        //right
        16,17,18,
        18,19,16,

        //left
        20,21,22,
        22,23,20
    };

    VertexAttribute attribsList[] =
    {
        sizeof(Vec3)/sizeof(float),//Position
        sizeof(Vec2) / sizeof(float) //texcoord
    };

    m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
        {
            (void*)verticesList,
            sizeof(Vertex),
            sizeof(verticesList) / sizeof(Vertex),                          // number of vertices

            attribsList,
            sizeof(attribsList) / sizeof(VertexAttribute)
        },

        {
            (void*)indicesList,
            sizeof(indicesList)
        }
    );

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

    projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.1f, 100.0f);

    // passing data into shaders using uniform
    UniformData data = { world , projection };
    m_uniform->setData(&data);


    m_graphicsEngine->clear(Vec4(0, 0, 0, 1));

    glfwPollEvents();

    m_graphicsEngine->setFaceCulling(CullType::BackFace);
    m_graphicsEngine->setWindingOrder(WindingOrder::ClockWise);
    m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
    m_graphicsEngine->setUniformBuffer(m_uniform, 0);
    m_graphicsEngine->setShaderProgram(m_shader);

    m_graphicsEngine->drawIndexedTriangles(TriangleType::TriangleList, 36);
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



