#include "MeshEntity.h"
#include "GraphicsEngine.h"
#include "Mesh.h"
#include "Texture.h"
#include "Game.h"

void MeshEntity::setMesh(const MeshPtr& mesh)
{
    m_mesh = mesh;
}

MeshPtr MeshEntity::getMesh()
{
    return m_mesh;
}

void MeshEntity::setTexture(const TexturePtr& texture)
{
    m_texture = texture;
}

TexturePtr MeshEntity::getTexture()
{
    return m_texture;
}

void MeshEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.viewProjectionMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());

    m_shader->setFloat("currentTime", data.currentTime);
}

void MeshEntity::onGraphicsUpdate(float deltaTime)
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
    engine->drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer
}

void MeshEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}