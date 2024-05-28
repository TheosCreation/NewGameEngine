#include "LightManager.h"
#include "Shader.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::createPointLight(const PointLight& newPointLight)
{
    m_pointLights[m_pointLightCount] = newPointLight;
    m_pointLightCount++;
}

void LightManager::createDirectionalLight(const DirectionalLight& newDirectionalLight)
{
    m_directionalLight = newDirectionalLight;
}

void LightManager::createSpotLight(const SpotLight& newSpotLight)
{
    m_spotLight = newSpotLight;
}

void LightManager::applyLighting(ShaderPtr shader)
{
    shader->setFloat("AmbientStrength", AmbientStrength);
    shader->setVec3("AmbientColor", AmbientColor);

    if (PointLightsStatus)
    {
        for (unsigned int i = 0; i < m_pointLightCount; i++)
        {
            std::string index = std::to_string(i);
            shader->setVec3("PointLightArray[" + index + "].Position", m_pointLights[i].Position);
            shader->setVec3("PointLightArray[" + index + "].Color", m_pointLights[i].Color);
            shader->setFloat("PointLightArray[" + index + "].SpecularStrength", m_pointLights[i].SpecularStrength);

            shader->setFloat("PointLightArray[" + index + "].AttenuationConstant", m_pointLights[i].AttenuationConstant);
            shader->setFloat("PointLightArray[" + index + "].AttenuationLinear", m_pointLights[i].AttenuationLinear);
            shader->setFloat("PointLightArray[" + index + "].AttenuationExponent", m_pointLights[i].AttenuationExponent);
        }

        shader->setUint("PointLightCount", m_pointLightCount);
    }
    else
    {
        shader->setUint("PointLightCount", 0);
    }

    if (DirectionalLightStatus)
    {
        //apply directional light to shader
        shader->setVec3("DirLight.Direction", m_directionalLight.Direction);
        shader->setVec3("DirLight.Color", m_directionalLight.Color);
        shader->setFloat("DirLight.SpecularStrength", m_directionalLight.SpecularStrength);
        shader->setInt("DirectionalLightStatus", 1);
    }
    else
    {
        shader->setInt("DirectionalLightStatus", 0);
    }
    
    // Make this so i can have multiple spotlights
    if (SpotlightStatus)
    {
        shader->setVec3("SpotLight1.Position", m_spotLight.Position);
        shader->setVec3("SpotLight1.Direction", m_spotLight.Direction);
        shader->setVec3("SpotLight1.Color", m_spotLight.Color);
        shader->setFloat("SpotLight1.SpecularStrength", m_spotLight.SpecularStrength);
        shader->setFloat("SpotLight1.CutOff", m_spotLight.CutOff);
        shader->setFloat("SpotLight1.AttenuationConstant", m_spotLight.AttenuationConstant);
        shader->setFloat("SpotLight1.AttenuationLinear", m_spotLight.AttenuationLinear);
        shader->setFloat("SpotLight1.AttenuationExponent", m_spotLight.AttenuationExponent);
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
    m_spotLight.Position = position;
}

void LightManager::setSpotlightDirection(glm::vec3 direction)
{
    m_spotLight.Direction = direction;
}
