#include "TerrainEntity.h"
#include "GraphicsEngine.h"
#include "VertexArrayObject.h"
#include "LightManager.h"

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

    smoothHeightMap(data, width, depth);
    smoothHeightMap(data, width, depth);
    smoothHeightMap(data, width, depth);
    smoothHeightMap(data, width, depth);
    smoothHeightMap(data, width, depth);

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

void TerrainEntity::setTexture1(const TexturePtr& texture)
{
    m_texture1 = texture;
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

void TerrainEntity::onGraphicsUpdate(UniformData data)
{
    GraphicsEntity::onGraphicsUpdate(data);

    m_shader->setMat4("VPMatrix", data.projectionMatrix * data.viewMatrix);
    m_shader->setMat4("modelMatrix", getModelMatrix());

    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::None);
    graphicsEngine.setWindingOrder(WindingOrder::ClockWise);
    LightManager::GetInstance().applyLighting(m_shader);
    if (m_texture != nullptr)
    {
        graphicsEngine.setTexture2D(m_texture, 0, "Texture0");

    }
    if (m_texture1 != nullptr)
    {
        graphicsEngine.setTexture2D(m_texture1, 3, "Texture1");
    }

    if (m_heightMap != nullptr)
    {
        graphicsEngine.setTexture2D(m_heightMap, 4, "HeightMap");
    }

    graphicsEngine.setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    graphicsEngine.drawIndexedTriangles(TriangleType::TriangleList, m_mesh->getNumIndices());//draw triangles through the usage of index buffer
}

void TerrainEntity::smoothHeightMap(std::vector<float>& heightData, uint width, uint depth)
{
    std::vector<float> smoothedData(heightData.size());

    // Apply a simple box blur filter
    for (uint row = 0; row < depth; ++row) {
        for (uint col = 0; col < width; ++col) {
            float sum = 0.0f;
            uint count = 0;

            // Iterate over a 3x3 grid around the current cell
            for (int r = -1; r <= 1; ++r) {
                for (int c = -1; c <= 1; ++c) {
                    uint newRow = std::clamp<int>(row + r, 0, depth - 1);
                    uint newCol = std::clamp<int>(col + c, 0, width - 1);
                    sum += heightData[newRow * width + newCol];
                    count++;
                }
            }

            smoothedData[row * width + col] = sum / count;
        }
    }

    // Copy the smoothed data back to the original heightData
    heightData = std::move(smoothedData);
}
