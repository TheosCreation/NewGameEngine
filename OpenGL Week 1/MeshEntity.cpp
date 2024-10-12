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
#include "ShadowMap.h"

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
}

void MeshEntity::onGraphicsUpdate(UniformData data)
{
    GraphicsEntity::onGraphicsUpdate(data);

    m_shader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());

    m_shader->setVec3("CameraPos", data.cameraPosition);

    m_shader->setFloat("ObjectShininess", getShininess());
    LightManager::GetInstance().applyLighting(m_shader);

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    if (m_texture != nullptr)
    {
        graphicsEngine.setTexture2D(m_texture, 0, "Texture0");
    }
    else
    {
        m_shader->setVec3("uColor", m_color);
    }

    auto skyboxTexture = ResourceManager::GetInstance().getSkyboxTexture();
    if (skyboxTexture)
    {
        graphicsEngine.setTextureCubeMap(skyboxTexture, 1, "Texture_Skybox");
    }

    if (m_reflectiveMap)
    {
        graphicsEngine.setTexture2D(m_reflectiveMap, 2, "ReflectionMap");
    }

    // Get the shadow map texture and bind it
    ShadowMapPtr shadowMapTexture = LightManager::GetInstance().getShadowMapTexture(); // Function to get the shadow map texture
    if (shadowMapTexture)
    {
        graphicsEngine.setTexture2D(shadowMapTexture, 3, "Texture_ShadowMap");
    }


    auto meshVBO = m_mesh->getVertexArrayObject();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer

    graphicsEngine.setTexture2D(nullptr, 0, "");
    graphicsEngine.setTextureCubeMap(nullptr, 1, "");
    graphicsEngine.setTexture2D(nullptr, 2, "");
    graphicsEngine.setTexture2D(nullptr, 3, "");
}

void MeshEntity::onShadowPass()
{
    // Retrieve the instance of the graphics engine
    auto& graphicsEngine = GraphicsEngine::GetInstance();

    // Set the shader used for shadow mapping
    if (m_shadowShader == nullptr) return;
    graphicsEngine.setShader(m_shadowShader);

    // Configure depth testing and culling settings
    graphicsEngine.setFaceCulling(CullType::BackFace);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setDepthFunc(DepthType::Less);

    // Set up the shadow-specific uniforms
    // These uniforms include the light's view and projection matrices
    auto& lightManager = LightManager::GetInstance();
    m_shadowShader->setMat4("VPLight", lightManager.getLightSpaceMatrix());

    if (m_mesh == nullptr) return;
    // Bind the vertex array object for the mesh
    auto meshVBO = m_mesh->getVertexArrayObject();
    
    graphicsEngine.setVertexArrayObject(meshVBO);

    // Draw the mesh to update the shadow map
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());
}

float MeshEntity::getShininess() const
{
    return m_shininess;
}

void MeshEntity::setShininess(const float shininess)
{
    m_shininess = shininess;
}
