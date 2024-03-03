#include "Window.h"
#include "Prerequisites.h"

Window::Window()
{
    if (!glfwInit())
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");
        return;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Create a GLFW window
    m_windowPtr = std::shared_ptr<GLFWwindow>(glfwCreateWindow(m_size.width, m_size.height, "TheoCreates | OpenGL 3D Game", nullptr, nullptr));
    if (!m_windowPtr)
    {
        OGL3D_ERROR("GLFW failed to initialize properly. Terminating program.");
        glfwTerminate();
        return;
    }

    // Make the window's OpenGL context current
    glfwMakeContextCurrent(getWindow());

    // Initialize GLEW or GLAD here if needed

    // Set GLFW user pointer to 'this' for access in callback functions
    glfwSetWindowUserPointer(getWindow(), this);

    // Set GLFW callbacks if needed (e.g., for input handling)

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
