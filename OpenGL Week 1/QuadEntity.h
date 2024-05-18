/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : QuadEntity.h
Description : creates a quad with its texture split 4 times
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

/**
 * @class QuadEntity
 * @brief Creates a quad with its texture split 4 times.
 */
class QuadEntity : public GraphicsEntity
{
public:
    /**
     * @brief Called when the quad entity is created.
     */
    virtual void onCreate();

    /**
     * @brief Sets the uniform data for the shader.
     * @param data The uniform data to set.
     */
    virtual void setUniformData(UniformData data);

    /**
     * @brief Sets the shader for the quad entity.
     * @param shader A shared pointer to the shader.
     */
    void setShader(const ShaderPtr& shader);

protected:
    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(float deltaTime);

private:
    VertexArrayObjectPtr m_mesh; //A shared pointer to the vertex array object representing the quad mesh.
};