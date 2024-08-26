/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Window.cpp
Description : Window class is a wrapper of a GLFWwindow to display the rendering from the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Window.h"
#include "Utils.h"

Window::Window()
{
    // Set GLFW window hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //Specify whether to create a forward-compatible context
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a GLFW window
    m_windowPtr = glfwCreateWindow(m_size.width, m_size.height, "TheoCreates | OpenGL 3D Game", nullptr, nullptr);
    if (!m_windowPtr)
    {
        Debug::LogError("GLFW failed to initialize properly. Terminating program.");
        glfwTerminate();
        return;
    }
    
    // Make the context current before initializing GLEW
    makeCurrentContext(vsync);

    // Initialize GLEW or GLAD here if needed
    if (glewInit() != GLEW_OK)
    {
        Debug::LogError("GLEW failed to initialize properly. Terminating program.");
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

glm::vec2 Window::getInnerSize()
{
    int width, height;
    glfwGetFramebufferSize(m_windowPtr, &width, &height);
    return glm::vec2(width, height);
}

GLFWwindow* Window::getWindow()
{
    return m_windowPtr;
}

void Window::makeCurrentContext(bool vsync)
{
    glfwMakeContextCurrent(m_windowPtr);

    glfwSwapInterval(vsync ? 1 : 0);
}

void Window::present()
{
    glfwSwapBuffers(m_windowPtr);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_windowPtr);
}
