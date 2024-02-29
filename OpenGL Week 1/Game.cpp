#include "Game.h"

Game::Game()
{
    //init GLFW ver 4.6
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //init window
    Window = glfwCreateWindow(800, 800, "First OpenGL Window", NULL, NULL);
    if (Window == NULL)
    {
        std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
        system("pause");

        onQuit();
    }
    glfwMakeContextCurrent(Window);

    //init GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
        system("pause");

        onQuit();
    }

    m_graphicsEngine->SetViewport(Rect(0, 0, 800, 800));
}

Game::~Game()
{
}

void Game::onCreate()
{
    //m_graphicsEngine->clear(Vec4(0,1,0,1));
    const float Vertices_Tri0[] = { // First triangle (top-left, bottom-left, bottom-right)
        -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Red
        -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,  // Green
        0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,  // Blue
    };
    const float Vertices_Tri1[] = { // Second triangle (bottom-right, top-left, top-right)
        -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Blue
        0.8f, 0.8f, 0.0f,   0.0f, 1.0f, 0.0f,  // Red
        0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,   // Cyan
    };

    m_triangleVAO = m_graphicsEngine->createVertexArrayObject({ (void*)Vertices_Tri0, sizeof(float) * 3, 3 });
}

void Game::onUpdate()
{
    glfwPollEvents();

    m_graphicsEngine->setVertexArrayObject(m_triangleVAO);

    m_graphicsEngine->drawTriangles(3, 0);

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



