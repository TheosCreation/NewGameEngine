#include "TerrainEntity.h"
#include "HeightMap.h"
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

    // Debug print height map data
    std::cout << "Height Map Width: " << width << ", Height: " << height << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Height Value [" << i << "]: " << static_cast<int>(textureData[i]) << std::endl;
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

            if (texX >= width || texZ >= height)
            {
                OGL3D_ERROR("Calculated texture coordinates out of bounds");
                continue; // Skip this iteration
            }

            float heightValue = textureData[texZ * width + texX] / 255.0f; // Normalize height value
            float posX = static_cast<float>(x) / (m_gridSize.x - 1) * m_width;
            float posY = heightValue * m_height;
            float posZ = static_cast<float>(z) / (m_gridSize.y - 1) * m_width;

            verticesList[vertexIndex] = {
                Vector3(posX, posY, posZ),
                glm::vec2(static_cast<float>(x) / (m_gridSize.x - 1), static_cast<float>(z) / (m_gridSize.y - 1)),
                Vector3(0.0f, 1.0f, 0.0f) // Placeholder for normals
            };

            // Debug print vertex positions
            std::cout << "Vertex [" << vertexIndex << "]: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;

            vertexIndex++;
        }
    }

    int index = 0;
    for (unsigned int row = 0; row < m_gridSize.y - 1; ++row)
    {
        for (unsigned int col = 0; col < m_gridSize.x - 1; ++col)
        {
            indicesList[index++] = row * m_gridSize.x + col;
            indicesList[index++] = row * m_gridSize.x + col + 1;
            indicesList[index++] = (row + 1) * m_gridSize.x + col;

            indicesList[index++] = (row + 1) * m_gridSize.x + col;
            indicesList[index++] = row * m_gridSize.x + col + 1;
            indicesList[index++] = (row + 1) * m_gridSize.x + col + 1;
        }
    }

    // Calculate normals using central difference
    float invCellSpacing = 1.0f / (2.0f * m_width / (m_gridSize.x - 1));
    for (unsigned int row = 0; row < m_gridSize.y; ++row)
    {
        for (unsigned int col = 0; col < m_gridSize.x; ++col)
        {
            float rowNeg = textureData[(row == 0 ? row : row - 1) * width + col] / 255.0f;
            float rowPos = textureData[(row < m_gridSize.y - 1 ? row + 1 : row) * width + col] / 255.0f;
            float colNeg = textureData[row * width + (col == 0 ? col : col - 1)] / 255.0f;
            float colPos = textureData[row * width + (col < m_gridSize.x - 1 ? col + 1 : col)] / 255.0f;

            float x = (rowNeg - rowPos);
            if (row == 0 || row == m_gridSize.y - 1)
            {
                x *= 2.0f;
            }

            float y = (colPos - colNeg);
            if (col == 0 || col == m_gridSize.x - 1)
            {
                y *= 2.0f;
            }

            Vector3 tangentZ(0.0f, x * invCellSpacing, 1.0f);
            Vector3 tangentX(1.0f, y * invCellSpacing, 0.0f);
            Vector3 normal = glm::cross(tangentZ, tangentX);
            normal = glm::normalize(normal);

            verticesList[row * m_gridSize.x + col].normal = normal;
        }
    }

    static const VertexAttribute attribsList[] = {
        { 3 }, // numElements position attribute
        { 2 }, // numElements texture coordinates attribute
        { 3 }  // numElements normal attribute
    };

    VertexBufferDesc vertexBufferDesc = {
        (void*)verticesList,           // Pointer to vertex list
        sizeof(Vertex),                // Size of a single vertex
        numVertices,                   // Number of vertices
        (VertexAttribute*)attribsList, // Pointer to vertex attributes list
        3                              // Number of elements in attrib list
    };

    IndexBufferDesc indexBufferDesc = {
        (void*)indicesList,
        sizeof(uint) * numIndices
    };

    m_mesh = GraphicsEngine::GetInstance().createVertexArrayObject(
        vertexBufferDesc,
        indexBufferDesc
    );

    delete[] verticesList;
    delete[] indicesList;
}
void TerrainEntity::onCreate()
{
}

void TerrainEntity::setUniformData(UniformData data)
{
    m_shader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());
}

void TerrainEntity::setShader(const ShaderPtr& shader)
{
    m_shader = shader;
}

void TerrainEntity::onGraphicsUpdate(float deltaTime)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::None);
    graphicsEngine.setWindingOrder(WindingOrder::ClockWise);
    graphicsEngine.setDepthFunc(DepthType::Less);

    if (m_texture)
    {
        graphicsEngine.setTexture2D(m_texture, 0);
    }
    else
    {
        m_shader->setVec3("uColor", m_color);
    }

    // During the graphics update, we call the draw function
    graphicsEngine.setVertexArrayObject(m_mesh); // Bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices()); // Draw triangles through the usage of index buffer
}