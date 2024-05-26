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
}

void MeshEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::BackFace); // draw only the front faces, the back faces are discarded
    engine->setWindingOrder(WindingOrder::ClockWise); //consider the position of vertices in clock wise way.

    if (m_texture)
    {
        engine->setTexture2D(m_texture->getTexture2D(), 0);
    }

    auto skyboxTexture = getGame()->getSkyboxTexture();
    if (skyboxTexture)
    {
        engine->setTextureCubeMap(skyboxTexture->getTextureCubeMap(), 0);
    }

    //during the graphics update, we call the draw function
    auto meshVBO = m_mesh->getVertexArrayObject();
    engine->setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    engine->drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer
}