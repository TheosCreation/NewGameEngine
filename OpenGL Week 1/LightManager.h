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
#include "ShadowMap.h"

/**
 * @class LightManager
 * @brief Handles lighting and passing into shaders.
 */
class LightManager
{
public:
    /**
     * @brief Static method to get the singleton instance of the LightManager class.
     * @return The singleton instance of the LightManager.
     */
    static LightManager& GetInstance()
    {
        static LightManager instance;
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copying.
    LightManager(const LightManager&) = delete;
    LightManager& operator=(const LightManager&) = delete;
    
    /**
    * @brief Initilizes the lightmanager on program start only and creates the shadowmaps
    */
    void Init();

    /**
    * @brief Creates a point light and adds it to the manager.
    * @param newPointLight The point light to be added.
    */
    void createPointLight(const PointLight& newPointLight);

    /**
     * @brief Creates a directional light and adds it to the manager.
     * @param newDirectionalLight The directional light to be added.
     */
    void createDirectionalLight(const DirectionalLight& newDirectionalLight);

    /**
     * @brief Creates a spotlight and adds it to the manager.
     * @param newSpotLight The spotlight to be added.
     */
    void createSpotLight(const SpotLight& newSpotLight);

    /**
     * @brief Apply lighting to the shader.
     * @param shader A shared pointer to the shader.
     */
    void applyLighting(ShaderPtr shader) const;
    void applyShadows(ShaderPtr shader) const;

    /**
     * @brief Gets the status of point lights.
     * @return True if point lights are enabled, false otherwise.
     */
    bool getPointLightsStatus() const;

    /**
     * @brief Sets the status of point lights.
     * @param status The new status of point lights.
     */
    void setPointLightsStatus(bool status);

    /**
     * @brief Gets the status of the directional light.
     * @return True if the directional light is enabled, false otherwise.
     */
    bool getDirectionalLightStatus() const;
    void BindShadowMap(int index);
    void UnBindShadowMap(int index);
    uint getDirectionalLightCount() const;
    Mat4 getLightSpaceMatrix(int index) const;

    void setShadowMapTexture(ShadowMapPtr shadowMap, int index);

    /**
    * @brief Sets the status of the directional light.
    * @param status The new status of the directional light.
    */
    void setDirectionalLightStatus(bool status);

    /**
     * @brief Gets the status of the spotlight.
     * @return True if the spotlight is enabled, false otherwise.
     */
    bool getSpotlightStatus() const;

    /**
     * @brief Sets the status of the spotlight.
     * @param status The new status of the spotlight.
     */
    void setSpotlightStatus(bool status);

    /**
     * @brief Sets the position of the spotlight.
     * @param position The new position of the spotlight.
     */
    void setSpotlightPosition(Vector3 position);

    /**
     * @brief Sets the direction of the spotlight.
     * @param direction The new direction of the spotlight.
     */
    void setSpotlightDirection(Vector3 direction);

    void reset();
    void clearLights();

protected:

private:
    /**
     * @brief Private constructor for the LightManager class.
     */
    LightManager() = default;

    /**
     * @brief Private destructor for the LightManager class.
     */
    ~LightManager() = default;

    float AmbientStrength = 0.2f; //The strength of the ambient light
    Vector3 AmbientColor = Vector3(1.0f, 1.0f, 1.0f); //The color of the ambient light
    static const int MAX_POINT_LIGHTS = 20; //The maximum number of point lights
    PointLight m_pointLights[MAX_POINT_LIGHTS] = {}; //Array of point lights
    uint m_pointLightCount = 0; //The current count of point lights

    static const int MAX_DIRECTIONAL_LIGHTS = 2; //The maximum number of point lights
    DirectionalLight m_directionalLights[MAX_DIRECTIONAL_LIGHTS] = {};
    uint m_directionalLightCount = 0; //The current count of directional lights

    SpotLight m_spotLight; //The spotlight

    ShadowMapPtr m_shadowMapTexture[MAX_DIRECTIONAL_LIGHTS] = {};

    bool PointLightsStatus = true; //The status of point lights
    bool DirectionalLightStatus = true; //The status of the directional light
    bool SpotlightStatus = true; //The status of the spotlight
};