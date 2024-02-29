#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "ShaderLoader.h"

GLFWwindow* Window = nullptr;
GLuint Program_FixedTri = 0;
GLuint Program_PositionOnly = 0;
GLuint Program_VertexColor = 0;
GLuint Program_ColorFade = 0;

GLfloat Vertices_Tri0[] = { // First triangle (top-left, bottom-left, bottom-right)
  -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Red
  -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,  // Green
  0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,  // Blue
};

GLfloat Vertices_Tri1[] = { // Second triangle (bottom-right, top-left, top-right)
  -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Blue
  0.8f, 0.8f, 0.0f,   0.0f, 1.0f, 0.0f,  // Red
  0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,   // Cyan
};

GLuint VBO_Tri0, VAO_Tri0;
GLuint VBO_Tri1, VAO_Tri1;

float CurrentTime = 0;

void MakeTriangle(GLuint* VB0, GLuint* VA0, GLfloat* vertices, GLsizei numVertices) {
    glGenBuffers(1, *&VB0);
    glBindBuffer(GL_ARRAY_BUFFER, *VB0);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, *&VA0);
    glBindVertexArray(*VA0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void InitialSetup()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 800, 800);

    Program_FixedTri = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
    Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/PositionOnly.vert", "Resources/Shaders/FixedColor.frag");
    Program_VertexColor = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColor.frag");
    Program_ColorFade = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColorFade.frag");

    // First triangle (VAO_Tri0, VBO_Tri0)
    //glGenVertexArrays(1, &VAO_Tri0);
    //glBindVertexArray(VAO_Tri0);
    //glGenBuffers(1, &VBO_Tri0);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO_Tri0);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Tri0), Vertices_Tri0, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);
    MakeTriangle(&VBO_Tri0, &VAO_Tri0, Vertices_Tri0, sizeof(Vertices_Tri0) / sizeof(GLfloat));

    // Second triangle (VAO_Tri1, VBO_Tri1)
    //glGenVertexArrays(1, &VAO_Tri1);
    //glBindVertexArray(VAO_Tri1);
    //glGenBuffers(1, &VBO_Tri1);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO_Tri1);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices_Tri1), Vertices_Tri1, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);
    MakeTriangle(&VBO_Tri1, &VAO_Tri1, Vertices_Tri1, sizeof(Vertices_Tri1) / sizeof(GLfloat));
}

void Update()
{
    glfwPollEvents();

    CurrentTime = (float)glfwGetTime();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Program_ColorFade);
    glBindVertexArray(VAO_Tri0);
    // Render the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(Program_ColorFade);
    glBindVertexArray(VAO_Tri1);
    // Render the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Send variables to the shaders via Uniform
    GLint CurrentTimeLoc = glGetUniformLocation(Program_ColorFade, "CurrentTime");
    glUniform1f(CurrentTimeLoc, CurrentTime);

    // Unbind assets
    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(Window);
}

int main()
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

        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Window);

    //init GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLFW failed to initialize properly. Terminating program." << std::endl;
        system("pause");

        glfwTerminate();
        return -1;
    }

    InitialSetup();

    //run funcs while window open
    while (glfwWindowShouldClose(Window) == false)
    {
        Update();

        Render();
    }

    glfwTerminate();
    return 0;

}