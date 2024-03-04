#include "GraphicsEngine.h"
#include <glew.h>
#include <glfw3.h>

//float CurrentTime;
VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc)
{
    return std::make_shared<VertexArrayObject>(vbDesc);
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
{
    return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
}

UniformBufferPtr GraphicsEngine::createUniform(const UniformBufferDesc& desc)
{
    return std::make_shared<UniformBuffer>(desc);
}

ShaderProgramPtr GraphicsEngine::createShaderProgram(const ShaderProgramDesc& desc)
{
    return std::make_shared<ShaderProgram>(desc);
}

void GraphicsEngine::clear(const Vec4& color)
{
    //glEnable(GL_DEPTH_TEST);
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthFunc(GL_LESS);
}

void GraphicsEngine::setFaceCulling(const CullType& type)
{
    auto cullType = GL_BACK;

    if (type == CullType::FrontFace) cullType = GL_FRONT;
    else if (type == CullType::BackFace) cullType = GL_BACK;
    else if (type == CullType::Both) cullType = GL_FRONT_AND_BACK;

    glEnable(GL_CULL_FACE);
    glCullFace(cullType);
}

void GraphicsEngine::setWindingOrder(const WindingOrder& type)
{
    auto orderType = GL_CW;

    if (type == WindingOrder::ClockWise) orderType = GL_CW;
    else if (type == WindingOrder::CounterClockWise) orderType = GL_CCW;

    glFrontFace(orderType);
}

void GraphicsEngine::SetViewport(const Rect& size)
{
    glViewport(size.left, size.top, size.width, size.height);
}

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
    glBindVertexArray(vao->getId());
}

void GraphicsEngine::setUniformBuffer(const UniformBufferPtr& buffer, uint slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void GraphicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

void GraphicsEngine::drawTriangles(const TriangleType& triangleType, uint vertexCount, uint offset)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
        case TriangleType::TriangleList: { glTriType = GL_TRIANGLES; break; }
        case TriangleType::TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }
    glDrawArrays(glTriType, offset, vertexCount);
}

void GraphicsEngine::drawIndexedTriangles(const TriangleType& triangleType, uint indicesCount)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
        case TriangleType::TriangleList: { glTriType = GL_TRIANGLES; break; }
        case TriangleType::TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }
    glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr);
}
