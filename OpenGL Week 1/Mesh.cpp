#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <filesystem>
#include "VertexMesh.h"
#include "Game.h"
#include "GraphicsEngine.h"

Mesh::Mesh(const wchar_t* path, ResourceManager* manager) : Resource(path, manager)
{
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    
    std::string warn;
    std::string err;
    
    auto inputfile = std::filesystem::path(path).string();
    
    bool res = tinyobj::LoadObj(&attribs, &shapes, nullptr, &warn, &err, inputfile.c_str(), nullptr);
    
    if (!err.empty()) OGL3D_ERROR("Mesh | creation failed with the following errors:");
    
    if (!res) OGL3D_ERROR("Mesh | not created successfully");
    
    std::vector<VertexMesh> list_vertices;
    std::vector<unsigned int> list_indices;
    
    size_t vertex_buffer_size = 0;
    
    for (size_t s = 0; s < shapes.size(); s++)
    {
        vertex_buffer_size += shapes[s].mesh.indices.size();
    }
    
    list_vertices.reserve(vertex_buffer_size);
    list_indices.reserve(vertex_buffer_size);
    
    size_t index_global_offset = 0;
    
    if (shapes.size() == 0 || shapes.size() > 1) OGL3D_ERROR("Mesh not created successfully");
    
    for (size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
    
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
    
            for (unsigned char v = 0; v < num_face_verts; v++)
            {
                tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];
    
                tinyobj::real_t vx = attribs.vertices[(int)(index.vertex_index * 3 + 0)];
                tinyobj::real_t vy = attribs.vertices[(int)(index.vertex_index * 3 + 1)];
                tinyobj::real_t vz = -attribs.vertices[(int)(index.vertex_index * 3 + 2)];
    
                tinyobj::real_t tx = 0;
                tinyobj::real_t ty = 0;
                if (attribs.texcoords.size())
                {
                    tx = attribs.texcoords[(int)(index.texcoord_index * 2 + 0)];
                    ty = 1.0f - attribs.texcoords[(int)(index.texcoord_index * 2 + 1)];
                }
                // For now, assuming default normals
                glm::vec3 normal(0.0f);
    
                VertexMesh vertex(glm::vec3(vx, vy, vz), glm::vec2(tx, ty), normal);
                list_vertices.push_back(vertex);
    
                list_indices.push_back((unsigned int)index_global_offset + v);
            }
    
            index_offset += num_face_verts;
            index_global_offset += num_face_verts;
        }
    }
    
    auto engine = manager->getGame()->getGraphicsEngine();
    
    const VertexAttribute attribsList[] = {
        { 3 }, // numElements position attribute
        { 2 }, // numElements texture coordinates attribute
        { 3 }  // numElements normal attribute
    };
    
    m_vao = engine->createVertexArrayObject(
        // vertex buffer
        {
            (void*)&list_vertices[0],
            sizeof(VertexMesh),
            (uint)list_vertices.size(),
            (VertexAttribute*)attribsList,
            3
        },
        // index buffer
        {
            (void*)&list_indices[0],
            (uint)list_indices.size()
        }
        );
}

Mesh::~Mesh()
{
}

VertexArrayObjectPtr Mesh::getVertexArrayObject()
{
	return m_vao;
}
