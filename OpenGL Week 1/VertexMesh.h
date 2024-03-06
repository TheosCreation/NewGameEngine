#pragma once
#include "Math.h"

class  VertexMesh
{
public:
	VertexMesh() :m_position(), m_normal(), m_texcoord()
	{
	}
	VertexMesh(const  glm::vec3& position,  const  glm::vec3& normal, const  glm::vec2& texcoord) :
		m_position(position),
		m_normal(normal),
		m_texcoord(texcoord)
	{
	}
	VertexMesh(const VertexMesh& vertex) :
		m_position(vertex.m_position),
		m_normal(vertex.m_normal),
		m_texcoord(vertex.m_texcoord)
	{
	}
public:
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_texcoord;

};