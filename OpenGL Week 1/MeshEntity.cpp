/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : MeshEntity.cpp
Description : Entity type that renders meshes
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "MeshEntity.h"
#include "GraphicsEngine.h"
#include "VertexArrayObject.h" 
#include "Mesh.h"
#include "Game.h"

void MeshEntity::setMesh(const MeshPtr& mesh)
{
    m_mesh = mesh;
}

MeshPtr MeshEntity::getMesh()
{
    return m_mesh;
}

void MeshEntity::setReflectiveMapTexture(const TexturePtr& texture)
{
    m_reflectiveMap = texture;
}

void MeshEntity::onCreate()
{
}

void MeshEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());

    m_shader->setVec3("CameraPos", data.cameraPosition);

    m_shader->setFloat("ObjectShininess", getShininess());
    m_shader->setInt("Texture_Skybox", 1);
    m_shader->setInt("Texture_Skybox", 1);
    m_shader->setInt("ReflectionMap", 2);
}

void MeshEntity::onGraphicsUpdate(float deltaTime)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::BackFace); // draw only the front faces, the back faces are discarded
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise); //consider the position of vertices in clock wise way.

    if (m_texture)
    {
        graphicsEngine.setTexture2D(m_texture, 0);
    }
    else
    {
        m_shader->setVec3("uColor", m_color);
    }

    auto skyboxTexture = ResourceManager::GetInstance().getSkyboxTexture();
    if (skyboxTexture)
    {
        graphicsEngine.setTextureCubeMap(skyboxTexture, 1);
    }
    
    if (m_reflectiveMap)
    {
        graphicsEngine.setTexture2D(m_reflectiveMap, 2);
    }

    //during the graphics update, we call the draw function
    auto meshVBO = m_mesh->getVertexArrayObject();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer
}

float MeshEntity::getShininess() const
{
    return m_shininess;
}

void MeshEntity::setShininess(const float shininess)
{
    m_shininess = shininess;
}
