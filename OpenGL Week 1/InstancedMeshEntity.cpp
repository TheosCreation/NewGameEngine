/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : InstancedMeshEntity.cpp
Description : Entity type that renders instanced meshes
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "InstancedMeshEntity.h"
#include "GraphicsEngine.h"
#include "InstancedMesh.h"
#include "VertexArrayObject.h" 
#include "Game.h"

void InstancedMeshEntity::setMesh(const InstancedMeshPtr& mesh)
{
    m_mesh = mesh;
}

InstancedMeshPtr InstancedMeshEntity::getMesh()
{
	return m_mesh;
}

void InstancedMeshEntity::onCreate()
{
}

void InstancedMeshEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);

    m_shader->setVec3("CameraPos", data.cameraPosition);

    m_shader->setFloat("ObjectShininess", getShininess());
    m_shader->setInt("Texture_Skybox", 1);
    m_shader->setInt("ReflectionMap", 2);
}

void InstancedMeshEntity::onGraphicsUpdate(float deltaTime)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::BackFace); // draw only the front faces, the back faces are discarded
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise); //consider the position of vertices in clock wise way.

    if (m_texture)
    {
        graphicsEngine.setTexture2D(m_texture, 0);
    }

    auto skyboxTexture = ResourceManager::GetInstance().getSkyboxTexture();
    if (skyboxTexture)
    {
        graphicsEngine.setTextureCubeMap(skyboxTexture, 0);
    }

    if (m_reflectiveMap)
    {
        graphicsEngine.setTexture2D(m_reflectiveMap, 2);
    }

    //during the graphics update, we call the draw function
    auto meshVBO = m_mesh->getVertexArrayObject();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTrianglesInstanced(TriangleType::TriangleList, meshVBO->getNumIndices(), m_mesh->getInstanceCount());
}