/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : InstancedMeshEntity.h
Description : Entity type that renders instanced meshes
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once

#include "MeshEntity.h"

/**
 * @class InstancedMeshEntity
 * @brief An entity that renders instanced meshes.
 */
class InstancedMeshEntity : public MeshEntity
{
public:
    /**
     * @brief Sets the instanced mesh for this entity.
     * @param mesh A shared pointer to the instanced mesh.
     */
    void setMesh(const InstancedMeshPtr& mesh);

    /**
     * @brief Gets the instanced mesh for this entity.
     * @return A shared pointer to the instanced mesh.
     */
    InstancedMeshPtr getMesh();

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
    void onGraphicsUpdate(UniformData data) override;
    void onGeometryPass(UniformData data) override;

    void onShadowPass(int index) override;

private:
    InstancedMeshPtr m_mesh; //A shared pointer to the instanced mesh.
};