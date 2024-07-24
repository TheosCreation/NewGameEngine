#pragma once

#include "GraphicsEntity.h"

class TerrainEntity : public GraphicsEntity
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

    void generateTerrainMesh();

protected:
    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(float deltaTime);

private:
    VertexArrayObjectPtr m_mesh; //A shared pointer to the vertex array object representing the terrian
    glm::ivec2 m_gridSize = { 128, 128 }; // Grid size (number of vertices along width and height)
    float m_width = 100.0f;      // Width of the terrain
    float m_height = 20.0f;      // Height scale of the terrain
};

