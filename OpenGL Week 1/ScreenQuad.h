/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : ScreenQuad.h
Description : Entity type that renders a quad
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

/**
 * @class ScreenQuad
 * @brief Entity type that renders a quad.
 */
class ScreenQuad : public GraphicsEntity
{
public:

    /**
     * @brief Called when the quad entity is created.
     */
    virtual void onCreate();

    void updateVertices(Vector2 size);

    /**
     * @brief Sets the shader for the quad entity.
     * @param shader A shared pointer to the shader.
     */
    void setShader(const ShaderPtr& shader);

    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(float deltaTime);

    void setSize(Rect size);

private:
    VertexArrayObjectPtr m_mesh; //A shared pointer to the vertex array object representing the quad mesh.
};