#include "GrapicsEngine.h"
#include "VertexArrayObject.h"

//GLuint VBO_Tri0, VAO_Tri0;
//GLuint VBO_Tri1, VAO_Tri1;
//
//GLfloat Vertices_Tri0[] = { // First triangle (top-left, bottom-left, bottom-right)
//  -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Red
//  -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,  // Green
//  0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,  // Blue
//};
//
//GLfloat Vertices_Tri1[] = { // Second triangle (bottom-right, top-left, top-right)
//  -0.8f, 0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Blue
//  0.8f, 0.8f, 0.0f,   0.0f, 1.0f, 0.0f,  // Red
//  0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,   // Cyan
//};
//
//GLuint Program_FixedTri = 0;
//GLuint Program_PositionOnly = 0;
//GLuint Program_VertexColor = 0;
//GLuint Program_ColorFade = 0;
//
//float CurrentTime;
VertexArrayObjectPtr GrapicsEngine::createVertexArrayObject(const VertexBufferData& data)
{
    return std::make_shared<VertexArrayObject>(data);
}

void GrapicsEngine::SetViewport(const Rect& size)
{
    glViewport(size.left, size.top, size.width, size.height);
}

GrapicsEngine::GrapicsEngine()
{
}

GrapicsEngine::~GrapicsEngine()
{
}

void GrapicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}

void GrapicsEngine::drawTriangles(unsigned int vertexCount, unsigned int offset)
{
    glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}

void GrapicsEngine::InitialSetup()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glViewport(0, 0, 800, 800);

    //Program_FixedTri = ShaderLoader::CreateProgram("Resources/Shaders/FixedTriangle.vert", "Resources/Shaders/FixedColor.frag");
    //Program_PositionOnly = ShaderLoader::CreateProgram("Resources/Shaders/PositionOnly.vert", "Resources/Shaders/FixedColor.frag");
    //Program_VertexColor = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColor.frag");
    //Program_ColorFade = ShaderLoader::CreateProgram("Resources/Shaders/VertexColor.vert", "Resources/Shaders/VertexColorFade.frag");

    //MakeTriangle(&VBO_Tri0, &VAO_Tri0, Vertices_Tri0, sizeof(Vertices_Tri0) / sizeof(GLfloat));

    //MakeTriangle(&VBO_Tri1, &VAO_Tri1, Vertices_Tri1, sizeof(Vertices_Tri1) / sizeof(GLfloat));
}

//void GrapicsEngine::MakeTriangle(GLuint* VB0, GLuint* VA0, GLfloat* vertices, GLsizei numVertices) {
//    glGenBuffers(1, *&VB0);
//    glBindBuffer(GL_ARRAY_BUFFER, *VB0);
//    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, *&VA0);
//    glBindVertexArray(*VA0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//}

void GrapicsEngine::Render(GLFWwindow* WindowToRenderTo)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //
    //glUseProgram(Program_ColorFade);
    //glBindVertexArray(VAO_Tri0);
    //// Render the triangle
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //
    //glUseProgram(Program_ColorFade);
    //glBindVertexArray(VAO_Tri1);
    //// Render the triangle
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    // Send variables to the shaders via Uniform
    //GLint CurrentTimeLoc = glGetUniformLocation(Program_ColorFade, "CurrentTime");
    //glUniform1f(CurrentTimeLoc, CurrentTime);

    // Unbind assets
    //glBindVertexArray(0);
    //glUseProgram(0);

    glfwSwapBuffers(WindowToRenderTo);
}

void GrapicsEngine::clear(const Vec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GrapicsEngine::Update()
{
    //CurrentTime = (float)glfwGetTime();
}