#include "Window.h"
#include "Utils.h"

Window::Window()
{
    // Set GLFW window hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //Specify whether to create a forward-compatible context
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFW window
    m_windowPtr = glfwCreateWindow(m_size.width, m_size.height, "TheoCreates | OpenGL 3D Game", nullptr, nullptr);
    if (!m_windowPtr)
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");
        glfwTerminate();
        return;
    }
    
    // Make the context current before initializing GLEW
    makeCurrentContext(1);

    // Initialize GLEW or GLAD here if needed
    if (glewInit() != GLEW_OK)
    {
        OGL3D_ERROR("GLEW failed to initialize properly. Terminating program.");
        glfwTerminate();
        return;
    }

    // Set GLFW user pointer to 'this' for access in callback functions
    glfwSetWindowUserPointer(m_windowPtr, this);

    // Show the window
    glfwShowWindow(m_windowPtr);
}

Window::~Window()
{
    glfwMakeContextCurrent(nullptr);
    // Destroy the GLFW window
    glfwDestroyWindow(m_windowPtr);
    // Terminate GLFW
    glfwTerminate();
}

Rect Window::getInnerSize()
{
    int width, height;
    glfwGetFramebufferSize(m_windowPtr, &width, &height);
    return Rect(0, 0, width, height);
}

GLFWwindow* Window::getWindow()
{
    return m_windowPtr;
}

void Window::makeCurrentContext(bool vsync)
{
    glfwMakeContextCurrent(m_windowPtr);

    glfwSwapInterval(vsync ? 1 : 0);

    glEnable(GL_DEPTH_TEST);
}

void Window::present()
{
    glfwSwapBuffers(m_windowPtr);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_windowPtr);
}
