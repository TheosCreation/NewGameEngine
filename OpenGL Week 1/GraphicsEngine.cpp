#include "GraphicsEngine.h"
#include <glew.h>
#include <glfw3.h>

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc)
{
    return std::make_shared<VertexArrayObject>(vbDesc);
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
{
    return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
}

ShaderProgramPtr GraphicsEngine::createShaderProgram(const ShaderProgramDesc& desc)
{
    return std::make_shared<ShaderProgram>(desc);
}

Texture2DPtr GraphicsEngine::createTexture2D(const Texture2DDesc& desc)
{
    return std::make_shared<Texture2D>(desc);
}

void GraphicsEngine::clear(const glm::vec4& color)
{
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::setFaceCulling(const CullType& type)
{
    auto cullType = GL_BACK;
    if (type == CullType::None)
    {
        glDisable(GL_CULL_FACE);
    }
    else {
        if (type == CullType::FrontFace) cullType = GL_FRONT;
        else if (type == CullType::BackFace) cullType = GL_BACK;
        else if (type == CullType::Both) cullType = GL_FRONT_AND_BACK;

        glEnable(GL_CULL_FACE);
        glCullFace(cullType);
    }
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

void GraphicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
    glUseProgram(program->getId());
}

void GraphicsEngine::setTexture2D(const Texture2DPtr& texture, uint slot)
{
    auto glSlot = GL_TEXTURE0 + slot;
    glActiveTexture(glSlot); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture->getId());

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