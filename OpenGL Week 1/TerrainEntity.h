#pragma once

#include "GraphicsEntity.h"
#include "HeightMap.h"

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

    void generateTerrainMesh(HeightMapPtr _heightMap);

protected:
    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(UniformData data);

    void smoothHeightMap(std::vector<float>& heightData, uint width, uint depth);

private:
    VertexArrayObjectPtr m_mesh; //A shared pointer to the vertex array object representing the terrian
};

