#include "HexagonEntity.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "Texture.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 rgb;
};

void HexagonEntity::onCreate()
{
    static bool vaoCreated = false;
    static std::shared_ptr<VertexArrayObject> sharedVAO;

    if (!vaoCreated) {
        glm::vec3 position_list[] =
        {
            //front face 
            glm::vec3(0.0f, -0.5f, 0.1f),
            glm::vec3(-0.433f, -0.25f, 0.1f),
            glm::vec3(0.433f, -0.25f, 0.1f),
            glm::vec3(0.433f, 0.25f, 0.1f),
            glm::vec3(-0.433f, 0.25f, 0.1f),
            glm::vec3(0.0f, 0.5f, 0.1f)
        };

        glm::vec3 rgb_list[] =
        {
            { glm::vec3(1.0f, 0.0f, 0.0f) },
            { glm::vec3(0.0f, 1.0f, 0.0f) },
            { glm::vec3(0.0f, 0.0f, 1.0f) },
        };

        Vertex verticesList[] =
        {
            //front face
            { position_list[0],rgb_list[0] },
            { position_list[1],rgb_list[0] },
            { position_list[2],rgb_list[1] },
            { position_list[3],rgb_list[1] },
            { position_list[4],rgb_list[2] },
            { position_list[5],rgb_list[2] }
        };

        uint indicesList[] =
        {
            //front face
            2, 1, 0, // Triangle 1
            1, 2, 3, // Triangle 2
            1, 3, 4, // Triangle 3
            5, 4, 3, // Triangle 4
        };

        static const VertexAttribute attribsList[] = {
            { 3 }, //numElements position attribute
            { 3 } //numElements rgb 
        };

        sharedVAO = getGame()->getGraphicsEngine()->createVertexArrayObject(
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

        vaoCreated = true;
    }

    m_mesh = sharedVAO;
}

void HexagonEntity::setTexture(const TexturePtr& texture)
{
    m_texture = texture;
}

void HexagonEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("mvpMatrix", data.mvpMatrix);
    m_shader->setFloat("currentTime", data.currentTime);
    m_shader->setVec3("flowingColor", data.color);
}

void HexagonEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}

void HexagonEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::BackFace);
    engine->setWindingOrder(WindingOrder::CounterClockWise);

    //during the graphcis update, we call the draw function
    engine->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    engine->drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer

}
