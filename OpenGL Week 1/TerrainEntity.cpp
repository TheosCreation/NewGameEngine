#include "TerrainEntity.h"
#include "GraphicsEngine.h"
#include "VertexArrayObject.h"

void TerrainEntity::generateTerrainMesh(HeightMapPtr _heightMap)
{
    if (!_heightMap) {
        // Handle the error if _heightMap is null
        return;
    }

    std::vector<float> data = _heightMap->getData();
    uint depth = _heightMap->getDepth();
    uint width = _heightMap->getWidth();
    float cellSpacing = _heightMap->getCellSpacing();

    uint numVertices = width * depth;
    uint numIndices = (width - 1) * (depth - 1) * 6;

    Vertex* verticesList = new Vertex[numVertices];
    uint* indicesList = new uint[numIndices];
    
    float halfWidth = (width - 1) * cellSpacing * 0.5f;
    float halfDepth = (depth - 1) * cellSpacing * 0.5f;
    float texU = 1.0f / (width - 1);
    float texV = 1.0f / (depth - 1);

    for (uint row = 0; row < depth; ++row) {
        float posZ = halfDepth - (row * cellSpacing);
        for (uint col = 0; col < width; ++col) {
            uint i = row * width + col;
            float posX = -halfWidth + (col * cellSpacing);
            float posY = data[i];

            verticesList[i].position = Vector3(posX, posY, posZ);
            verticesList[i].texCoords = Vector2(col * texU, row * texV);
            verticesList[i].normal = Vector3(0.0f, 1.0f, 0.0f);
        }
    }

    uint k = 0;
    for (uint row = 0; row < (width - 1); ++row) {
        for (uint col = 0; col < (depth - 1); ++col) {
            indicesList[k] = row * depth + col;
            indicesList[k + 1] = row * depth + col + 1;
            indicesList[k + 2] = (row + 1) * depth + col;

            indicesList[k + 3] = (row + 1) * depth + col;
            indicesList[k + 4] = row * depth + col + 1;
            indicesList[k + 5] = (row + 1) * depth + col + 1;

            k += 6;
        }
    }

    // Calculate normals using central difference
    float invCellSpacing = 1.0f / (2.0f * cellSpacing);
    for (uint row = 0; row < width; ++row) {
        for (uint col = 0; col < depth; ++col) {
            float rowNeg = data[(row == 0 ? row : row - 1) * depth + col];
            float rowPos = data[(row == width - 1 ? row : row + 1) * depth + col];
            float colNeg = data[row * depth + (col == 0 ? col : col - 1)];
            float colPos = data[row * depth + (col == depth - 1 ? col : col + 1)];

            float x = (rowNeg - rowPos);
            if (row == 0 || row == width - 1) {
                x *= 2.0f;
            }

            float y = (colPos - colNeg);
            if (col == 0 || col == depth - 1) {
                y *= 2.0f;
            }

            Vector3 tangentZ(0.0f, x * invCellSpacing, 1.0f);
            Vector3 tangentX(1.0f, y * invCellSpacing, 0.0f);
            Vector3 normal = glm::normalize(glm::cross(tangentZ, tangentX));
            unsigned int i = row * depth + col;
            verticesList[i].normal = normal;
        }
    }

    static const VertexAttribute attribsList[] = {
        { 3 }, // numElements position attribute
        { 2 }, // numElements texture coordinates attribute
        { 3 }  // numElements normal attribute
    };

    m_mesh = GraphicsEngine::GetInstance().createVertexArrayObject(
        //vertex buffer
        {
                (void*)verticesList,
                sizeof(Vertex), //size in bytes of a single composed vertex (in this case composed by vertex (3 nums* sizeof float) + texcoord (2 nums* sizeof float))
                numVertices,  //number of composed vertices,

                (VertexAttribute*)attribsList,
                3 //numelements attrib list
        },
        //index buffer
        {
            (void*)indicesList,
            numIndices
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