#include "LightManager.h"
#include "Shader.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::createPointLight(glm::vec3 position, glm::vec3 color, float specularStrength, float attenuationConstant, float attenuationLinear, float attenuationExponent)
{
    PointLights[PointLightCount].Position = position;
    PointLights[PointLightCount].Color = color;
    PointLights[PointLightCount].SpecularStrength = specularStrength;
    PointLights[PointLightCount].AttenuationConstant = attenuationConstant;
    PointLights[PointLightCount].AttenuationLinear = attenuationLinear;
    PointLights[PointLightCount].AttenuationExponent = attenuationExponent;
    PointLightCount++;
}

void LightManager::createDirectionalLight(glm::vec3 direction, glm::vec3 color, float specularStrength)
{
    DirectionalLight.Direction = direction;
    DirectionalLight.Color = color;
    DirectionalLight.SpecularStrength = specularStrength;
}

void LightManager::createSpotLight(glm::vec3 position, glm::vec3 direction, float cutOff)
{
    SpotLight.Position = position;
    SpotLight.Direction = direction;
    SpotLight.CutOff = cutOff;
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

            shader->setFloat("PointLightArray[" + index + "].AttenuationConstant", PointLights[i].AttenuationConstant);
            shader->setFloat("PointLightArray[" + index + "].AttenuationLinear", PointLights[i].AttenuationLinear);
            shader->setFloat("PointLightArray[" + index + "].AttenuationExponent", PointLights[i].AttenuationExponent);
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
        shader->setVec3("DirLight.Direction", DirectionalLight.Direction);
        shader->setVec3("DirLight.Color", DirectionalLight.Color);
        shader->setFloat("DirLight.SpecularStrength", DirectionalLight.SpecularStrength);
        shader->setInt("DirectionalLightStatus", 1);
    }
    else
    {
        shader->setInt("DirectionalLightStatus", 0);
    }
    
    if (SpotlightStatus)
    {
        shader->setVec3("SpotLight1.Position", SpotLight.Position);
        shader->setVec3("SpotLight1.Direction", SpotLight.Direction);
        shader->setFloat("SpotLight1.CutOff", SpotLight.CutOff); 
        shader->setInt("SpotLightStatus", 1);
    }
    else
    {
        shader->setInt("SpotLightStatus", 0);
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

void LightManager::setSpotlightPosition(glm::vec3 position)
{
    SpotLight.Position = position;
}

void LightManager::setSpotlightDirection(glm::vec3 direction)
{
    SpotLight.Direction = direction;
}
