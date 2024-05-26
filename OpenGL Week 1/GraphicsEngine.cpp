/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : GraphicsEngine.cpp
Description : GraphicsEngine class contains all the render functionality of opengl
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "GraphicsEngine.h"
#include <glew.h>
#include <glfw3.h>
#include "VertexArrayObject.h"
#include "Shader.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc)
{
    return std::make_shared<VertexArrayObject>(vbDesc);
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
{
    return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
}

ShaderPtr GraphicsEngine::createShader(const ShaderDesc& desc)
{
    return std::make_shared<Shader>(desc);
}

Texture2DPtr GraphicsEngine::createTexture2D(const Texture2DDesc& desc)
{
    return std::make_shared<Texture2D>(desc);
}

TextureCubeMapPtr GraphicsEngine::createTextureCubeMap(const TextureCubeMapDesc& desc)
{
    return std::make_shared<TextureCubeMap>(desc);
}

void GraphicsEngine::clear(const glm::vec4& color)
{
    setDepthFunc(DepthType::Less);
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

void GraphicsEngine::setDepthFunc(const DepthType& type)
{
    auto depthType = GL_LESS;
    if (type == DepthType::LessEqual) depthType = GL_LEQUAL;
    else if (type == DepthType::Less) depthType = GL_LESS;

    glDepthFunc(depthType);
}

void GraphicsEngine::setWindingOrder(const WindingOrder& type)
{
    auto orderType = GL_CW;

    if (type == WindingOrder::ClockWise) orderType = GL_CW;
    else if (type == WindingOrder::CounterClockWise) orderType = GL_CCW;

    glFrontFace(orderType);
}

void GraphicsEngine::setViewport(const Rect& size)
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

void GraphicsEngine::setShader(const ShaderPtr& program)
{
    glUseProgram(program->getId());
}

void GraphicsEngine::setTexture2D(const Texture2DPtr& texture, uint slot)
{
    auto glSlot = GL_TEXTURE0 + slot;
    glActiveTexture(glSlot); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture->getId());
}

void GraphicsEngine::setTextureCubeMap(const TextureCubeMapPtr& texture, uint slot)
{
    auto glSlot = GL_TEXTURE0 + slot;
    glActiveTexture(glSlot); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getId());
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

void GraphicsEngine::drawIndexedTrianglesInstanced(const TriangleType& triangleType, uint indicesCount, int instanceCount)
{
    auto glTriType = GL_TRIANGLES;

    switch (triangleType)
    {
        case TriangleType::TriangleList: { glTriType = GL_TRIANGLES; break; }
        case TriangleType::TriangleStrip: { glTriType = GL_TRIANGLE_STRIP; break; }
    }
    glDrawElementsInstanced(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr, instanceCount);
}