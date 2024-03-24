#include "HexagonEntity.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoords;
};

void HexagonEntity::onCreate()
{
    glm::vec3 position_list[] =
    {
        //front face 
        glm::vec3(0.0f, -0.5f, 0.1f),
        glm::vec3(-0.433f, -0.25f, 0.1f),
        glm::vec3(0.433f, -0.25f, 0.1f),
        glm::vec3(0.433f, 0.25f, 0.1f),
        glm::vec3(-0.433f, 0.25f, 0.1f),
        glm::vec3(0.0f, 0.5f, 0.1f),

        //back face
        glm::vec3(0.0f, -0.5f, -0.1f),
        glm::vec3(-0.433f, -0.25f, -0.1f),
        glm::vec3(0.433f, -0.25f, -0.1f),
        glm::vec3(0.433f, 0.25f, -0.1f),
        glm::vec3(-0.433f, 0.25f, -0.1f),
        glm::vec3(0.0f, 0.5f, -0.1f),
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
        { position_list[1],texcoord_list[2] },
        { position_list[2],texcoord_list[3] },
        { position_list[3],texcoord_list[2] },
        { position_list[4],texcoord_list[1] },
        { position_list[5],texcoord_list[0] },
        
        //back face face
        { position_list[6],texcoord_list[1] },
        { position_list[7],texcoord_list[2] },
        { position_list[8],texcoord_list[3] },
        { position_list[9],texcoord_list[2] },
        { position_list[10],texcoord_list[1] },
        { position_list[11],texcoord_list[0] },
    };

    uint indicesList[] =
    {
        //front face
        0, 1, 2, // Triangle 1
        3, 2, 1, // Triangle 2
        4, 3, 1, // Triangle 3
        3, 4, 5, // Triangle 4
        
        //back face
        8, 7, 6, // Triangle 1
        7, 8, 9, // Triangle 2
        7, 9, 10, // Triangle 3
        11, 10, 9, // Triangle 4

        //side face 1
        7, 1, 0,
        0, 6, 7,
        //side face 2
        10, 4, 1,
        1, 7, 10,
        //side face 3
        11, 5, 4,
        4, 10, 11,
        //side face 4
        9, 3, 5,
        5, 11, 9,
        //side face 5
        8, 2, 3,
        3, 9, 8,
        //side face 6
        6, 0, 2,
        2, 8, 6,
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

void HexagonEntity::setTexture(const TexturePtr& texture)
{
    m_texture = texture;
}

void HexagonEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::FrontFace);
    engine->setWindingOrder(WindingOrder::ClockWise);

    getGame()->getGraphicsEngine()->setTexture2D(m_texture->getTexture2D(), 0);
    //during the graphcis update, we call the draw function
    getGame()->getGraphicsEngine()->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    getGame()->getGraphicsEngine()->drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer
}
