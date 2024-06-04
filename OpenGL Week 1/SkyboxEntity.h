/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : SkyboxEntity.h
Description : 
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "MeshEntity.h"

class SkyboxEntity : public MeshEntity
{
public:
    /**
     * @brief Called when the entity is created.
     */
    void onCreate() override;

    /**
     * @brief Sets the uniform data for the shader.
     * @param data The uniform data to set.
     */
    void setUniformData(UniformData data) override;

    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    void onGraphicsUpdate(float deltaTime) override;
};