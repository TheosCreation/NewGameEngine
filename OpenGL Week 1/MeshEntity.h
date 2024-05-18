/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : MeshEntity.h
Description : Entity type that renders meshes
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "GraphicsEntity.h"

/**
 * @class MeshEntity
 * @brief An entity type that renders meshes.
 */
class MeshEntity : public GraphicsEntity
{
public:
    /**
     * @brief Sets the mesh for this entity.
     * @param mesh A shared pointer to the mesh.
     */
    void setMesh(const MeshPtr& mesh);

    /**
     * @brief Gets the mesh for this entity.
     * @return A shared pointer to the mesh.
     */
    MeshPtr getMesh();

    /**
     * @brief Called when the entity is created.
     */
    virtual void onCreate();

    /**
     * @brief Sets the uniform data for the shader.
     * @param data The uniform data to set.
     */
    virtual void setUniformData(UniformData data);

    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(float deltaTime);

private:
    MeshPtr m_mesh; //A shared pointer to the mesh.
};