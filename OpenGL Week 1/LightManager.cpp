#include "LightManager.h"
#include "Shader.h"

LightManager::LightManager()
{
    // Initialize point lights
    PointLightArray[0].Position = glm::vec3(25.0f, 15.0f, 0.0f);
    PointLightArray[0].Color = glm::vec3(0.0f, 0.0f, 1.0f);
    PointLightArray[0].SpecularStrength = 1.0f;

    PointLightArray[1].Position = glm::vec3(-25.0f, 15.0f, 0.0f);
    PointLightArray[1].Color = glm::vec3(1.0f, 0.0f, 0.0f);
    PointLightArray[1].SpecularStrength = 1.0f;

    // Set the number of point lights
    PointLightCount = 2;
}

LightManager::~LightManager()
{
}

void LightManager::applyLighting(ShaderPtr shader)
{
    shader->setFloat("AmbientStrength", AmbientStrength);
    shader->setVec3("AmbientColor", AmbientColor);

    for (unsigned int i = 0; i < PointLightCount; ++i)
    {
        std::string index = std::to_string(i);
        shader->setVec3("PointLightArray[" + index + "].Position", PointLightArray[i].Position);
        shader->setVec3("PointLightArray[" + index + "].Color", PointLightArray[i].Color);
        shader->setFloat("PointLightArray[" + index + "].SpecularStrength", PointLightArray[i].SpecularStrength);
    }

    shader->setUint("PointLightCount", PointLightCount);
}