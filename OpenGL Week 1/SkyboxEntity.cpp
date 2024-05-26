#include "SkyboxEntity.h"
#include "GraphicsEngine.h"
#include "VertexArrayObject.h" 
#include "Mesh.h"
#include "Game.h"

void SkyboxEntity::onCreate()
{
}

void SkyboxEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.viewProjectionMatrix);
}

void SkyboxEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::FrontFace); // draw only the back faces, the front faces are discarded
    engine->setWindingOrder(WindingOrder::ClockWise); //consider the position of vertices in clock wise way.
    engine->setDepthFunc(DepthType::LessEqual);

    engine->setTextureCubeMap(m_texture->getTextureCubeMap(), 0);

    //during the graphics update, we call the draw function
    auto meshVBO = getMesh()->getVertexArrayObject();
    engine->setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    engine->drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer
}
