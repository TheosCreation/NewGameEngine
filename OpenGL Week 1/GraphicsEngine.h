/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : GraphicsEngine.h
Description : GraphicsEngine class contains all the render functionality of opengl
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"
#include "Math.h"
#include "ResourceManager.h"

/**
 * @class GraphicsEngine
 * @brief Contains all the render functionality of OpenGL.
 */
class GraphicsEngine
{
public:
    /**
     * @brief Constructor for the GraphicsEngine class.
     */
    GraphicsEngine();

    /**
     * @brief Destructor for the GraphicsEngine class.
     */
    ~GraphicsEngine();

    /**
     * @brief Creates a Vertex Array Object (VAO) without an Index Buffer.
     * @param vbDesc Description of the Vertex Buffer.
     * @return A shared pointer to the created Vertex Array Object.
     */
    VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc);

    /**
     * @brief Creates a Vertex Array Object (VAO) with an Index Buffer.
     * @param vbDesc Description of the Vertex Buffer.
     * @param ibDesc Description of the Index Buffer.
     * @return A shared pointer to the created Vertex Array Object.
     */
    VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);

    /**
     * @brief Creates a Shader program.
     * @param desc Description of the Shader.
     * @return A shared pointer to the created Shader.
     */
    ShaderPtr createShader(const ShaderDesc& desc);

    /**
     * @brief Clears the screen with the specified color.
     * @param color The color to clear the screen with.
     */
    void clear(const glm::vec4& color);

    /**
     * @brief Sets the face culling mode.
     * @param type The type of face culling to use.
     */
    void setFaceCulling(const CullType& type);

    void setDepthFunc(const DepthType& type);

    /**
     * @brief Sets the winding order for front-facing polygons.
     * @param type The winding order to use.
     */
    void setWindingOrder(const WindingOrder& type);

    /**
     * @brief Sets the viewport size.
     * @param size The size of the viewport.
     */
    void setViewport(const Rect& size);

    void setMultiSampling();

    /**
     * @brief Sets the active Vertex Array Object (VAO).
     * @param vao A shared pointer to the Vertex Array Object to set.
     */
    void setVertexArrayObject(const VertexArrayObjectPtr& vao);

    /**
     * @brief Sets the active Shader program.
     * @param program A shared pointer to the Shader program to set.
     */
    void setShader(const ShaderPtr& program);

    /**
     * @brief Sets the active 2D Texture.
     * @param texture A shared pointer to the Texture2D to set.
     * @param slot The texture slot to bind the texture to.
     */
    void setTexture2D(const TexturePtr& texture, uint slot);

    void setTextureCubeMap(const TexturePtr& texture, uint slot);

    /**
     * @brief Draws triangles.
     * @param triangleType The type of triangles to draw.
     * @param vertexCount The number of vertices to draw.
     * @param offset The offset to start drawing from.
     */
    void drawTriangles(const TriangleType& triangleType, uint vertexCount, uint offset);

    /**
     * @brief Draws indexed triangles.
     * @param triangleType The type of triangles to draw.
     * @param indicesCount The number of indices to draw.
     */
    void drawIndexedTriangles(const TriangleType& triangleType, uint indicesCount);

    /**
     * @brief Draws indexed triangles with instancing.
     * @param triangleType The type of triangles to draw.
     * @param indicesCount The number of indices to draw.
     * @param instanceCount The number of instances to draw.
     */
    void drawIndexedTrianglesInstanced(const TriangleType& triangleType, uint indicesCount, int instanceCount);
};