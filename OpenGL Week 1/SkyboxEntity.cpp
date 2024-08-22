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
    glm::mat4 viewNoTranslationMatrix = glm::mat3(data.viewMatrix);
    m_shader->setMat4("VPMatrix", data.projectionMatrix * viewNoTranslationMatrix);
}

void SkyboxEntity::onGraphicsUpdate(float deltaTime)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::FrontFace); // draw only the back faces, the front faces are discarded
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise); //consider the position of vertices in clock wise way.
    graphicsEngine.setDepthFunc(DepthType::LessEqual);

    graphicsEngine.setTextureCubeMap(m_texture, 1);

    //during the graphics update, we call the draw function
    auto meshVBO = getMesh()->getVertexArrayObject();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer
}
