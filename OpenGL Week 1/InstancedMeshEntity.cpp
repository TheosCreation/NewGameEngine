#include "InstancedMeshEntity.h"
#include "GraphicsEngine.h"
#include "InstancedMesh.h"
#include "Texture.h"
#include "Game.h"

void InstancedMeshEntity::setMesh(const InstancedMeshPtr& mesh)
{
    m_mesh = mesh;
}

InstancedMeshPtr InstancedMeshEntity::getMesh()
{
	return m_mesh;
}

void InstancedMeshEntity::setTexture(const TexturePtr& texture)
{
	m_texture = texture;
}

TexturePtr InstancedMeshEntity::getTexture()
{
	return m_texture;
}

void InstancedMeshEntity::setUniformData(UniformData data)
{
    std::vector<glm::mat4> transformedMatrices;
    for (int i = 0; i < m_mesh->getInstanceCount(); ++i) {
        glm::mat4 mvpMatrix = data.viewProjectionMatrix * m_mesh->m_instanceTransforms[i];
        transformedMatrices.push_back(mvpMatrix);
    }
    m_shader->setMat4Array("mvpMatrixs[0]", transformedMatrices.data(), m_mesh->getInstanceCount());

	m_shader->setFloat("currentTime", data.currentTime);
	m_shader->setVec3("flowingColor", data.color);
}

void InstancedMeshEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::None); // draw only the front faces, the back faces are discarded
    engine->setWindingOrder(WindingOrder::CounterClockWise); //consider the position of vertices in clock wise way.

    if (getTexture())
    {
        engine->setTexture2D(m_texture->getTexture2D(), 0);
    }
    //during the graphcis update, we call the draw function
    auto meshVBO = m_mesh->getVertexArrayObject();
    engine->setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline

    engine->drawIndexedTrianglesInstanced(TriangleType::TriangleList, meshVBO->getNumIndices(), m_mesh->getInstanceCount());
}

void InstancedMeshEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}