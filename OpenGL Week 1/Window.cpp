#include "Window.h"
#include "Prerequisites.h"

Window::Window()
{
    // Set GLFW window hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    //Specify whether to create a forward-compatible context
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Set the number of samples for multisampling
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

    

    // Create a GLFW window
    m_windowPtr = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_size.width, m_size.height, "TheoCreates | OpenGL 3D Game", nullptr, nullptr));
    if (!m_windowPtr)
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");
        glfwTerminate();
        return;
    }
    
    // Make the context current before initializing GLEW
    glfwMakeContextCurrent(getWindow());

    // Initialize GLEW or GLAD here if needed
    if (glewInit() != GLEW_OK)
    {
        OGL3D_ERROR("GLEW failed to initialize properly. Terminating program.");
        glfwTerminate();
        return;
    }

    // Set GLFW user pointer to 'this' for access in callback functions
    glfwSetWindowUserPointer(getWindow(), this);

    // Show the window
    glfwShowWindow(getWindow());
}

Window::~Window()
{
    // Destroy the GLFW window
    glfwDestroyWindow(getWindow());

    // Terminate GLFW
    glfwTerminate();
}

Rect Window::getInnerSize()
{
    int width, height;
    glfwGetFramebufferSize(getWindow(), &width, &height);
    return Rect(width, height);
}

GLFWwindow* Window::getWindow()
{
    return m_windowPtr.get();
}

void Window::makeCurrentContext()
{
    glfwMakeContextCurrent(getWindow());
}

void Window::present(bool vsync)
{
    glfwSwapInterval(vsync ? 1 : 0);
    glfwSwapBuffers(getWindow());
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(getWindow());
}
