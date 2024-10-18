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
}

void SkyboxEntity::onGraphicsUpdate(UniformData data)
{
    GraphicsEntity::onGraphicsUpdate(data);

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setShader(m_shader);
    Mat4 viewNoTranslationMatrix = glm::mat3(data.viewMatrix);
    m_shader->setMat4("VPMatrix", data.projectionMatrix * viewNoTranslationMatrix);

    graphicsEngine.setFaceCulling(CullType::FrontFace);
    graphicsEngine.setDepthFunc(DepthType::LessEqual);
    if (m_texture != nullptr)
    {
        graphicsEngine.setTextureCubeMap(m_texture, 0, "Texture_Skybox");
    }

    //during the graphics update, we call the draw function
    auto meshVBO = getMesh()->getVertexArrayObject();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer

    graphicsEngine.setTextureCubeMap(nullptr, 0, "");
}

void SkyboxEntity::onGeometryPass(UniformData data)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setShader(m_geometryShader);
    graphicsEngine.setFaceCulling(CullType::FrontFace);
    graphicsEngine.setDepthFunc(DepthType::LessEqual);

    Mat4 viewNoTranslationMatrix = glm::mat3(data.viewMatrix);
    m_geometryShader->setMat4("VPMatrix", data.projectionMatrix * viewNoTranslationMatrix);

    if (m_texture != nullptr)
    {
        m_geometryShader->setTextureCubeMap(m_texture, 0, "Texture_Skybox");
    }


    //during the graphics update, we call the draw function
    auto meshVBO = getMesh()->getVertexArrayObject();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer

    m_geometryShader->setTextureCubeMap(nullptr, 0, "");
}
