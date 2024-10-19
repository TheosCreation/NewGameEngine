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
#include "GeometryBuffer.h"

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


void MeshEntity::onGraphicsUpdate(UniformData data)
{
    GraphicsEntity::onGraphicsUpdate(data);

    m_shader->setVec3("CameraPos", data.cameraPosition);
    LightManager::GetInstance().applyLighting(m_shader);
    GeometryBuffer::GetInstance().PopulateShader(m_shader);


    if (m_texture != nullptr)
    {
        m_shader->setTexture2D(m_texture, 0, "Texture0");
    }
    else
    {
        m_shader->setVec3("uColor", m_color);
    }

    auto skyboxTexture = ResourceManager::GetInstance().getSkyboxTexture();
    if (skyboxTexture)
    {
        m_shader->setTextureCubeMap(skyboxTexture, 1, "Texture_Skybox");
    }

    if (m_reflectiveMap)
    {
        m_shader->setTexture2D(m_reflectiveMap, 2, "ReflectionMap");
    }

    auto& lightManager = LightManager::GetInstance();
    //m_shader->setMat4("VPLight", lightManager.getLightSpaceMatrix());

    // Get the shadow map texture and bind it
    //ShadowMapPtr shadowMapTexture = lightManager.getShadowMapTexture(); // Function to get the shadow map texture
    //if (shadowMapTexture)
    //{
    //    m_shader->setTexture2D(shadowMapTexture, 3, "Texture_ShadowMap");
    //}


    auto meshVBO = m_mesh->getVertexArrayObject();

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setVertexArrayObject(meshVBO); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());//draw triangles through the usage of index buffer
}

void MeshEntity::onShadowPass()
{
    GraphicsEntity::onShadowPass();


    auto& lightManager = LightManager::GetInstance();
    m_shadowShader->setMat4("VPLight", lightManager.getLightSpaceMatrix());
    m_shadowShader->setMat4("modelMatrix", getModelMatrix());

    if (m_mesh == nullptr) return;

    // Bind the vertex array object for the mesh
    auto meshVBO = m_mesh->getVertexArrayObject();

    // Retrieve the instance of the graphics engine
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setVertexArrayObject(meshVBO);

    // Draw the mesh to update the shadow map
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());
}

void MeshEntity::onGeometryPass(UniformData data)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::BackFace);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setDepthFunc(DepthType::Less);
    graphicsEngine.setShader(m_geometryShader);

    m_geometryShader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);
    m_geometryShader->setMat4("modelMatrix", getModelMatrix());
    m_geometryShader->setFloat("ObjectShininess", getShininess());

    if (m_texture != nullptr)
    {
        graphicsEngine.setTexture2D(m_texture, 0, "Texture0");
    }

    // Bind the vertex array object for the mesh
    auto meshVBO = m_mesh->getVertexArrayObject();

    // Retrieve the instance of the graphics engine
    graphicsEngine.setVertexArrayObject(meshVBO);

    // Draw the mesh to update the shadow map
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, meshVBO->getNumIndices());
}

void MeshEntity::onLightingPass(UniformData data)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::BackFace);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setDepthFunc(DepthType::Less);
    graphicsEngine.setShader(m_lightingShader);

    GeometryBuffer::GetInstance().PopulateShader(m_lightingShader);

    m_lightingShader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);
    m_lightingShader->setMat4("ModelMatrix", getModelMatrix());
    m_lightingShader->setVec3("CameraPos", data.cameraPosition);

    auto& lightManager = LightManager::GetInstance();
    lightManager.applyLighting(m_lightingShader);
    //m_lightingShader->setMat4("VPLight", lightManager.getLightSpaceMatrix());

    if (m_mesh == nullptr) return;
    // Bind the vertex array object for the mesh
    auto meshVBO = m_mesh->getVertexArrayObject();

    // Retrieve the instance of the graphics engine
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
