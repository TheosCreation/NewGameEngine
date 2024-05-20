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

    /**
     * @brief Apply lighting to the shader
     * @param shader A shared pointer to the shader.
     */
    void applyLighting(ShaderPtr shader);

private:
    float AmbientStrength = 0.15f;
    glm::vec3 AmbientColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 LightPos = glm::vec3(-300.0f, 000.0f, 100.0f);
    float LightSpecularStrength = 1.0f;
};