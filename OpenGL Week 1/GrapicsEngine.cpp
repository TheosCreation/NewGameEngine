#include "GrapicsEngine.h"
#include "VertexArrayObject.h"
#include "UniformBuffer.h"
#include "ShaderProgram.h"

//float CurrentTime;
VertexArrayObjectPtr GrapicsEngine::createVertexArrayObject(const VertexBufferDesc& data)
{
    return std::make_shared<VertexArrayObject>(data);
}

UniformBufferPtr GrapicsEngine::createUniform(const UniformBufferDesc& desc)
{
    return std::make_shared<UniformBuffer>(desc);
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

void GrapicsEngine::setUniformBuffer(const UniformBufferPtr& buffer, uint slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void GrapicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

void GrapicsEngine::drawTriangles(const TriangleType& triangleType, uint vertexCount, uint offset)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
        case TriangleList: { glTriType = GL_TRIANGLES; break; }
        case TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }
    glDrawArrays(glTriType, offset, vertexCount);
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