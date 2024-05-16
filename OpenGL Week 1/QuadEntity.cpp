#include "QuadEntity.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
};

void QuadEntity::onCreate()
{
    glm::vec3 position_list[] =
    {
        //front face
        { glm::vec3(0.5f,-0.5f,0.5f) },
        { glm::vec3(0.5f,0.5f,0.5f) },
        { glm::vec3(-0.5f,0.5f,0.5f)},
        { glm::vec3(-0.5f,-0.5f,0.5f) }
    };

    glm::vec2 texcoord_list[] =
    {
        { glm::vec2(0.0f,0.0f) },
        { glm::vec2(0.0f,4.0f) },
        { glm::vec2(4.0f,0.0f) },
        { glm::vec2(4.0f,4.0f) }
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

    m_mesh = getGame()->getGraphicsEngine()->createVertexArrayObject(
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

void QuadEntity::setTexture(const TexturePtr& texture)
{
    m_texture = texture;
}

void QuadEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.uiViewProjectionMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());

    m_shader->setFloat("currentTime", data.currentTime);
}

void QuadEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}

void QuadEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::BackFace);
    engine->setWindingOrder(WindingOrder::CounterClockWise);

    engine->setTexture2D(m_texture->getTexture2D(), 0);

    //during the graphcis update, we call the draw function
    engine->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    engine->drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer

}