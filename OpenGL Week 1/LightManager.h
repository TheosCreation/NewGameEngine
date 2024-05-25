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

    void createPointLight(glm::vec3 position, glm::vec3 color, float specularStrength);

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

private:
    float AmbientStrength = 0.5f;
    glm::vec3 AmbientColor = glm::vec3(1.0f, 1.0f, 1.0f);
    static const int MAX_POINT_LIGHTS = 4;
    PointLight PointLights[MAX_POINT_LIGHTS] = {};
    uint PointLightCount = 0;

    bool PointLightsStatus = true;
    bool DirectionalLightStatus = true;
    bool SpotlightStatus = true;
};