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
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	auto inputfile = std::filesystem::path(path).string();

	std::string mtldir = inputfile.substr(0, inputfile.find_last_of("\\/"));


	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str(), mtldir.c_str()); 
	
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

	if (materials.size() == 0 || materials.size() > 1) OGL3D_ERROR("Mesh not created successfully");
	if (shapes.size() == 0 || shapes.size() > 1) OGL3D_ERROR("Mesh not created successfully");


	for (size_t m = 0; m < materials.size(); m++)
	{
		for (size_t s = 0; s < shapes.size(); s++)
		{
			size_t index_offset = 0;

			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				if (f >= 700)
					f = f;

				if (shapes[s].mesh.material_ids[f] != m) {
					unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
					index_offset += num_face_verts;
					continue;
				}

				unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

				glm::vec3 vertices_face[3];
				glm::vec2 texcoords_face[3];

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
					vertices_face[v] = glm::vec3(vx, vy, vz);
					texcoords_face[v] = glm::vec2(tx, ty);
				}

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

					tinyobj::real_t nx = 0;
					tinyobj::real_t ny = 0;
					tinyobj::real_t nz = 0;

					if (attribs.normals.size())
					{
						nx = attribs.normals[(int)(index.normal_index * 3 + 0)];
						ny = attribs.normals[(int)(index.normal_index * 3 + 1)];
						nz = -attribs.normals[(int)(index.normal_index * 3 + 2)];
					}


					VertexMesh vertex(glm::vec3(vx, vy, vz), glm::vec2(tx, ty), glm::vec3(nx, ny, nz));
					list_vertices.push_back(vertex);

					list_indices.push_back((unsigned int)index_global_offset + v);
				}

				index_offset += num_face_verts;
				index_global_offset += num_face_verts;
			}
		}
	}


	auto engine = manager->getGame()->getGraphicsEngine();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	const VertexAttribute attribsList[] = {
			{ 3 }, //numElements position attribute
			{ 2 }, //numElements texture coordinates attribute
			{ 3 } //numElements normal attribute
	};

	m_vao = engine->createVertexArrayObject(
		//vertex buffer
		{
				(void*)&list_vertices[0],
				sizeof(VertexMesh), //size in bytes of a single composed vertex (in this case composed by vertex (3 nums* sizeof float) + texcoord (2 nums* sizeof float))
				(uint)list_vertices.size(),  //number of composed vertices,

				(VertexAttribute*)attribsList,
				3 //numelements attrib list
		},
		//index buffer
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
