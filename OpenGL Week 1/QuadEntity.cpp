/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : QuadEntity.cpp
Description : Entity type that renders a quad
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "QuadEntity.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "VertexArrayObject.h"

void QuadEntity::onCreate()
{
    updateVertices({ 2.0f, 2.0f });
}

void QuadEntity::updateVertices(Vector2 size)
{
    Vector3 position_list[] =
    {
        //front face
        { Vector3(size.x / 2, -size.y / 2, 0.5f) },
        { Vector3(size.x / 2, size.y / 2, 0.5f) },
        { Vector3(-size.x / 2, size.y / 2, 0.5f)},
        { Vector3(-size.x / 2, -size.y / 2, 0.5f) }
    };

    glm::vec2 texcoord_list[] =
    {
        { glm::vec2(0.0f,0.0f) },
        { glm::vec2(0.0f,1.0f) },
        { glm::vec2(1.0f,0.0f) },
        { glm::vec2(1.0f,1.0f) }
    };

    Vertex verticesList[] =
    {
        //front face
        { position_list[0],texcoord_list[1] },
        { position_list[1],texcoord_list[0] },
        { position_list[2],texcoord_list[2] },
        { position_list[3],texcoord_list[3] }
    };

    uint indicesList[] =
    {
        //front face
        0,1,2,  //first triangle
        2,3,0,  //second triangle
    };

    static const VertexAttribute attribsList[] = {
        { 3 }, //numElements position attribute
        { 2 } //numElements texture coordinates attribute
    };

    m_mesh = GraphicsEngine::GetInstance().createVertexArrayObject(
        //vertex buffer
        {
                (void*)verticesList,
                sizeof(Vertex), //size in bytes of a single composed vertex (in this case composed by vertex (3 nums* sizeof float) + texcoord (2 nums* sizeof float))
                sizeof(verticesList) / sizeof(Vertex),  //number of composed vertices,

                (VertexAttribute*)attribsList,
                2 //numelements attrib list
        },
        //index buffer
        {
            (void*)indicesList,
            sizeof(indicesList)
        }
    );
}

void QuadEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.uiProjectionMatrix * data.uiViewMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());
}

void QuadEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}

void QuadEntity::onGraphicsUpdate(float deltaTime)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::None);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setDepthFunc(DepthType::Less);
    if (m_texture != nullptr)
    {
        graphicsEngine.setTexture2D(m_texture, 0);
    }
    else
    {
        m_shader->setVec3("uColor", m_color);
    }
    graphicsEngine.setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer
}

void QuadEntity::setTexture(uint textureId)
{
    m_texture = std::make_shared<Texture>();
    m_texture->setId(textureId);
}
