#include "GrapicsEngine.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"

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
VertexArrayObjectPtr GrapicsEngine::createVertexArrayObject(const VertexBufferDesc& data)
{
    return std::make_shared<VertexArrayObject>(data);
}

ShaderProgramPtr GrapicsEngine::createShaderProgram(const ShaderProgramDesc& desc)
{
    return std::make_shared<ShaderProgram>(desc);
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

void GrapicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

void GrapicsEngine::drawTriangles(unsigned int vertexCount, unsigned int offset)
{
    glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}

void GrapicsEngine::Render(GLFWwindow* WindowToRenderTo)
{
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