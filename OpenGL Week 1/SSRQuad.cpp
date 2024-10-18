#include "SSRQuad.h"
#include "LightManager.h"
#include "GeometryBuffer.h"
#include "ResourceManager.h"
#include "GraphicsEngine.h"
#include "VertexArrayObject.h"

void SSRQuad::onGraphicsUpdate(UniformData data)
{
    GraphicsEntity::onGraphicsUpdate(data);

    //LightManager::GetInstance().applyLighting(m_shader);
    GeometryBuffer::GetInstance().PopulateShader(m_shader);

   // auto& lightManager = LightManager::GetInstance();
    //m_shader->setMat4("VPLight", lightManager.getLightSpaceMatrix());

    // Get the shadow map texture and bind it
    //ShadowMapPtr shadowMapTexture = lightManager.getShadowMapTexture(); // Function to get the shadow map texture
    //if (shadowMapTexture)
    //{
    //    m_shader->setTexture2D(shadowMapTexture, 3, "Texture_ShadowMap");
    //}

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::None);
    graphicsEngine.setWindingOrder(WindingOrder::ClockWise);
    graphicsEngine.setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer

}
