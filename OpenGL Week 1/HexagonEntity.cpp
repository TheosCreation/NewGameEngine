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
        { position_list[0],texcoord_list[0] },
        { position_list[1],texcoord_list[1] },
        { position_list[2],texcoord_list[2] },
        { position_list[3],texcoord_list[3] },
        { position_list[4],texcoord_list[0] },
        { position_list[5],texcoord_list[1] },
        
        //back face face
        { position_list[6],texcoord_list[0] },
        { position_list[7],texcoord_list[1] },
        { position_list[8],texcoord_list[2] },
        { position_list[9],texcoord_list[3] },
        { position_list[10],texcoord_list[0] },
        { position_list[11],texcoord_list[1] },
    };

    uint indicesList[] =
    {
        //front face
        2, 1, 0, // Triangle 1
        1, 2, 3, // Triangle 2
        1, 3, 4, // Triangle 3
        5, 4, 3, // Triangle 4

        //back face
        6, 7, 8, // Triangle 1
        9, 8, 7, // Triangle 2
        10, 9, 7, // Triangle 3
        9, 10, 11, // Triangle 4

        //side face 1
        0, 1, 7,
        7, 6, 0,
        //side face 2
        1, 4, 10,
        10, 7, 1,
        //side face 3
        4, 5, 11,
        11, 10, 4,
        //side face 4
        5, 3, 9,
        9, 11, 5,
        //side face 5
        3, 2, 8,
        8, 9, 3,
        //side face 6
        2, 0, 6,
        6, 8, 2,
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

void HexagonEntity::setShader(const ShaderProgramPtr& shader)
{
    m_shader = shader;
}

void HexagonEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::BackFace);
    engine->setWindingOrder(WindingOrder::ClockWise);

    getGame()->getGraphicsEngine()->setShaderProgram(m_shader);

    //during the graphcis update, we call the draw function
    getGame()->getGraphicsEngine()->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    getGame()->getGraphicsEngine()->drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer

}
