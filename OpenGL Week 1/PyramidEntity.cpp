#include "PyramidEntity.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
};

void PyramidEntity::onCreate()
{
    glm::vec3 position_list[] =
    {
        // Base of the pyramid
        { glm::vec3(-0.5f, -0.5f, -0.5f) },
        { glm::vec3(0.5f, -0.5f, -0.5f) },
        { glm::vec3(0.5f, -0.5f, 0.5f) },
        { glm::vec3(-0.5f, -0.5f, 0.5f) },

        // Apex of the pyramid
        { glm::vec3(0.0f, 0.5f, 0.0f) }
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
        // Base of the pyramid
        { position_list[0], texcoord_list[1] },
        { position_list[1], texcoord_list[0] },
        { position_list[2], texcoord_list[2] },
        { position_list[3], texcoord_list[3] },

        // Apex of the pyramid
        { position_list[4], texcoord_list[0] }
    };

    uint indicesList[] =
    {
        //base of the pyramid
        0,1,2,  //first triangle
        0,2,3,  //second triangle

        //front face
        0,1,4,
        //back face
        1,2,4,
        //right face
        2,3,4,
        //left face
        3,0,4
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

void PyramidEntity::setTexture(const TexturePtr& texture)
{
    m_texture = texture;
}

void PyramidEntity::onGraphicsUpdate(float deltaTime)
{
    getGame()->getGraphicsEngine()->setTexture2D(m_texture->getTexture2D(), 0);
    //during the graphcis update, we call the draw function
    getGame()->getGraphicsEngine()->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    getGame()->getGraphicsEngine()->drawIndexedTriangles(TriangleType::TriangleList, 18);//draw triangles through the usage of index buffer
}
