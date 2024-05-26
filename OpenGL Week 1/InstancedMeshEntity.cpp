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
    m_shader->setMat4("VPMatrix", data.viewProjectionMatrix);
}

void InstancedMeshEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::BackFace); // draw only the front faces, the back faces are discarded
    engine->setWindingOrder(WindingOrder::ClockWise); //consider the position of vertices in clock wise way.
    engine->setDepthFunc(DepthType::Less);

    if (m_texture)
    {
        engine->setTexture2D(m_texture->getTexture2D(), 0);
    }
    //during the graphics update, we call the draw function
    auto meshVBO = m_mesh->getVertexArrayObject();
    engine->setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    engine->drawIndexedTrianglesInstanced(TriangleType::TriangleList, meshVBO->getNumIndices(), m_mesh->getInstanceCount());
}