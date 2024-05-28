/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : LightManager.h
Description : Handles lighting and passing into shaders
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once

#include "Utils.h"
#include "Math.h"
#include <vector>

/**
 * @class InputManager
 * @brief Handles inputs from the player/user of the program.
 */
class LightManager
{
public:
    /**
     * @brief Constructor for the LightManager class.
     */
    LightManager();

    /**
     * @brief Destructor for the LightManager class.
     */
    ~LightManager();

    void createPointLight(const PointLight& newPointLight);
    void createDirectionalLight(const DirectionalLight& newDrectionalLight);
    void createSpotLight(const SpotLight& newSpotLight);

    /**
     * @brief Apply lighting to the shader
     * @param shader A shared pointer to the shader.
     */
    void applyLighting(ShaderPtr shader);

    bool getPointLightsStatus();
    void setPointLightsStatus(bool status);

    bool getDirectionalLightStatus();
    void setDirectionalLightStatus(bool status);

    bool getSpotlightStatus();
    void setSpotlightStatus(bool status);
    void setSpotlightPosition(glm::vec3 position);
    void setSpotlightDirection(glm::vec3 direction);

private:
    float AmbientStrength = 0.15f;
    glm::vec3 AmbientColor = glm::vec3(1.0f, 1.0f, 1.0f);
    static const int MAX_POINT_LIGHTS = 4;
    PointLight m_pointLights[MAX_POINT_LIGHTS] = {};
    uint m_pointLightCount = 0;

    DirectionalLight m_directionalLight;

    SpotLight m_spotLight;

    bool PointLightsStatus = true;
    bool DirectionalLightStatus = true;
    bool SpotlightStatus = true;
};