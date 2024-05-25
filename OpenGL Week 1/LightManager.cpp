#include "LightManager.h"
#include "Shader.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::createPointLight(glm::vec3 position, glm::vec3 color, float specularStrength)
{
    PointLights[PointLightCount].Position = position;
    PointLights[PointLightCount].Color = color;
    PointLights[PointLightCount].SpecularStrength = specularStrength;
    PointLightCount++;
}

void LightManager::applyLighting(ShaderPtr shader)
{
    shader->setFloat("AmbientStrength", AmbientStrength);
    shader->setVec3("AmbientColor", AmbientColor);

    if (PointLightsStatus)
    {
        for (unsigned int i = 0; i < PointLightCount; i++)
        {
            std::string index = std::to_string(i);
            shader->setVec3("PointLightArray[" + index + "].Position", PointLights[i].Position);
            shader->setVec3("PointLightArray[" + index + "].Color", PointLights[i].Color);
            shader->setFloat("PointLightArray[" + index + "].SpecularStrength", PointLights[i].SpecularStrength);
        }

        shader->setUint("PointLightCount", PointLightCount);
    }
    else
    {
        shader->setUint("PointLightCount", 0);
    }

    if (DirectionalLightStatus)
    {
        //apply directional light to shader
    }
    else
    {
        //shader->setUint("PointLightCount", 0); 
    }
    
    if (SpotlightStatus)
    {
        //apply spotlight to shader
    }
    else
    {
        //shader->setUint("PointLightCount", 0);
    }
}

bool LightManager::getPointLightsStatus()
{
    return PointLightsStatus;
}

void LightManager::setPointLightsStatus(bool status)
{
    PointLightsStatus = status;
}

bool LightManager::getDirectionalLightStatus()
{
    return DirectionalLightStatus;
}

void LightManager::setDirectionalLightStatus(bool status)
{
    DirectionalLightStatus = status;
}

bool LightManager::getSpotlightStatus()
{
    return SpotlightStatus;
}

void LightManager::setSpotlightStatus(bool status)
{
    SpotlightStatus = status;
}
