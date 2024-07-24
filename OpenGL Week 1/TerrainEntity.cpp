#include "TerrainEntity.h"
#include "Texture2D.h"
#include "GraphicsEngine.h"
#include "Game.h"
#include "VertexArrayObject.h"

void TerrainEntity::generateTerrainMesh()
{
    if (!m_heightmap)
    {
        OGL3D_ERROR("Heightmap texture not set");
        return;
    }

    unsigned char* textureData = m_heightmap->getData();
    if (!textureData)
    {
        OGL3D_ERROR("Failed to retrieve texture data");
        return;
    }

    int width = m_heightmap->getWidth();
    int height = m_heightmap->getHeight();

    if (width <= 0 || height <= 0)
    {
        OGL3D_ERROR("Invalid texture dimensions");
        return;
    }

    int numVertices = m_gridSize.x * m_gridSize.y;
    int numIndices = (m_gridSize.x - 1) * (m_gridSize.y - 1) * 6;

    Vertex* verticesList = new Vertex[numVertices];
    uint* indicesList = new uint[numIndices];

    int vertexIndex = 0;
    for (int z = 0; z < m_gridSize.y; ++z)
    {
        for (int x = 0; x < m_gridSize.x; ++x)
        {
            int texX = x * (width / m_gridSize.x);
            int texZ = z * (height / m_gridSize.y);

            if (texX < 0 || texX >= width || texZ < 0 || texZ >= height)
            {
                OGL3D_ERROR("Texture coordinates out of bounds");
                delete[] verticesList;
                delete[] indicesList;
                return;
            }

            float heightValue = textureData[texZ * width + texX] / 255.0f; // Normalize height value
            float posX = static_cast<float>(x) / (m_gridSize.x - 1) * m_width;
            float posY = heightValue * m_height;
            float posZ = static_cast<float>(z) / (m_gridSize.y - 1) * m_width;

            verticesList[vertexIndex] = { glm::vec3(posX, posY, posZ), glm::vec2(static_cast<float>(x) / (m_gridSize.x - 1), static_cast<float>(z) / (m_gridSize.y - 1)), glm::vec3(0.0f, 1.0f, 0.0f) };
            vertexIndex++;
        }
    }

    int index = 0;
    for (int z = 0; z < m_gridSize.y - 1; ++z)
    {
        for (int x = 0; x < m_gridSize.x - 1; ++x)
        {
            int topLeft = z * m_gridSize.x + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * m_gridSize.x + x;
            int bottomRight = bottomLeft + 1;

            indicesList[index++] = topLeft;
            indicesList[index++] = bottomLeft;
            indicesList[index++] = topRight;
            indicesList[index++] = topRight;
            indicesList[index++] = bottomLeft;
            indicesList[index++] = bottomRight;
        }
    }

    static const VertexAttribute attribsList[] = {
        { 3 }, // numElements position attribute
        { 2 }, // numElements texture coordinates attribute
        { 3 }  // numElements normal attribute
    };

    m_mesh = getGame()->getGraphicsEngine()->createVertexArrayObject(
        // Vertex buffer
        {
            (void*)verticesList,
            sizeof(Vertex), // Size in bytes of a single composed vertex (in this case composed of vertex (3 nums * sizeof(float)) + texcoord (2 nums * sizeof(float)) + normal (3 nums * sizeof(float)))
            sizeof(verticesList) / sizeof(Vertex),  // Number of composed vertices
            (VertexAttribute*)attribsList,
            3 // Num elements in attrib list
        },
        // Index buffer
        {
            (void*)indicesList,
            sizeof(indicesList)
        }
    );

    delete[] verticesList;
    delete[] indicesList;
}


void TerrainEntity::onCreate()
{
}

void TerrainEntity::setUniformData(UniformData data)
{
}

void TerrainEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}

void TerrainEntity::onGraphicsUpdate(float deltaTime)
{
    auto engine = getGame()->getGraphicsEngine();
    engine->setFaceCulling(CullType::BackFace);
    engine->setWindingOrder(WindingOrder::ClockWise);
    engine->setDepthFunc(DepthType::Less);

    if (m_heightmap)
    {
        engine->setTexture2D(m_heightmap, 0);
    }

    // During the graphics update, we call the draw function
    engine->setVertexArrayObject(m_mesh); // Bind vertex buffer to graphics pipeline
    engine->drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices()); // Draw triangles through the usage of index buffer
}
