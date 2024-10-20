#include "LightManager.h"
#include "Shader.h"

void LightManager::createPointLight(const PointLight& newPointLight)
{
    m_pointLights[m_pointLightCount] = newPointLight;
    m_pointLightCount++;
}

void LightManager::createDirectionalLight(const DirectionalLight& newDirectionalLight)
{
    m_directionalLights[m_directionalLightCount] = newDirectionalLight;
    m_directionalLightCount++;
}

void LightManager::createSpotLight(const SpotLight& newSpotLight)
{
    m_spotLight = newSpotLight;
}

void LightManager::applyLighting(ShaderPtr shader) const
{
    shader->setFloat("AmbientStrength", AmbientStrength);
    shader->setVec3("AmbientColor", AmbientColor);

    if (PointLightsStatus)
    {
        for (unsigned int i = 0; i < m_pointLightCount; i++)
        {
            std::string index = std::to_string(i);
            shader->setVec3("PointLightArray[" + index + "].Base.Color", m_pointLights[i].Color);
            shader->setFloat("PointLightArray[" + index + "].Base.SpecularStrength", m_pointLights[i].SpecularStrength);

            shader->setVec3("PointLightArray[" + index + "].Position", m_pointLights[i].Position);
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
        for (unsigned int i = 0; i < m_directionalLightCount; i++)
        {
            std::string index = std::to_string(i);
            shader->setVec3("DirLightArray[" + index + "].Base.Color", m_directionalLights[i].Color);
            shader->setFloat("DirLightArray[" + index + "].Base.SpecularStrength", m_directionalLights[i].SpecularStrength);

            shader->setVec3("DirLightArray[" + index + "].Direction", m_directionalLights[i].Direction);

            shader->setFloat("DirLightArray[" + index + "].Base.SpecularStrength", m_directionalLights[i].SpecularStrength);
        }
        //apply directional light to shader
        shader->setUint("DirectionalLightCount", m_directionalLightCount);
    }
    else
    {
        shader->setUint("DirectionalLightCount", 0);
    }
    
    // Make this so i can have multiple spotlights
    if (SpotlightStatus)
    {
        shader->setVec3("SpotLight1.Base.Color", m_spotLight.Color);
        shader->setFloat("SpotLight1.Base.SpecularStrength", m_spotLight.SpecularStrength);
        shader->setVec3("SpotLight1.Position", m_spotLight.Position);
        shader->setVec3("SpotLight1.Direction", m_spotLight.Direction);
        shader->setFloat("SpotLight1.CutOff", m_spotLight.CutOff);
        shader->setFloat("SpotLight1.OuterCutOff", m_spotLight.OuterCutOff);
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

void LightManager::applyShadows(ShaderPtr shader) const
{
    //bindings 5 - 6
    for (unsigned int i = 0; i < m_directionalLightCount; i++)
    {
        std::string index = std::to_string(i);
        shader->setTexture2D(m_shadowMapTexture[i]->getId(), 5 + i, "Texture_ShadowMap[" + index + "]");
        shader->setMat4("VPLight[" + index + "]", getLightSpaceMatrix(i));
    }
}

Mat4 LightManager::getLightSpaceMatrix(int index) const
{
    // Validate index
    if (index < 0 || index >= m_directionalLightCount) {
        return Mat4(); // Return identity matrix if index is out of range
    }

    // Check if the directional light is active
    if (!DirectionalLightStatus) {
        return Mat4(); // Return identity matrix if the light is inactive
    }

    // Get the directional light properties
    const DirectionalLight& light = m_directionalLights[index];

    // Orthographic projection for shadow mapping
    float sceneExtent = 1500.0f; // Adjust based on your scene's size
    Mat4 projection = glm::ortho(-sceneExtent, sceneExtent, -sceneExtent, sceneExtent, 0.1f, 2000.0f);

    // Normalize the direction vector
    Vector3 lightDirection = Normalize(light.Direction);

    // Position the light far from the scene
    Vector3 lightPosition = -lightDirection * 450.0f; // Move the light far away along the direction

    // Define the view matrix for the directional light
    Mat4 view = glm::lookAt(lightPosition, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

    // Combine the projection and view matrices to get the light-space matrix
    Mat4 lightSpaceMatrix = projection * view;

    return lightSpaceMatrix;
}

void LightManager::setShadowMapTexture1(ShadowMapPtr texture)
{
    m_shadowMapTexture[0] = texture;
}

ShadowMapPtr LightManager::getShadowMapTexture1() const
{
    return m_shadowMapTexture[0];
}

void LightManager::setShadowMapTexture2(ShadowMapPtr texture)
{
    m_shadowMapTexture[1] = texture;
}

ShadowMapPtr LightManager::getShadowMapTexture2() const
{
    return m_shadowMapTexture[1];
}

void LightManager::setDirectionalLightStatus(bool status)
{
    DirectionalLightStatus = status;
}

bool LightManager::getSpotlightStatus() const
{
    return SpotlightStatus;
}

void LightManager::setSpotlightStatus(bool status)
{
    SpotlightStatus = status;
}

void LightManager::setSpotlightPosition(Vector3 position)
{
    m_spotLight.Position = position;
}

void LightManager::setSpotlightDirection(Vector3 direction)
{
    m_spotLight.Direction = direction;
}

void LightManager::reset()
{
    DirectionalLightStatus = true;
    SpotlightStatus = true;
    PointLightsStatus = true; 
    clearLights();
}

void LightManager::clearLights()
{
    // Reset point lights
    m_pointLightCount = 0;
    for (auto& pointLight : m_pointLights)
    {
        pointLight = PointLight(); // Reset each point light to its default state
    }

    // Reset the spot light
    m_spotLight = SpotLight(); // Reset the spot light to its default state

    // Reset the directional lights
    m_directionalLightCount = 0;
    for (auto& dirLight : m_directionalLights)
    {
        dirLight = DirectionalLight(); // Reset each directional light to its default state
    }
}
