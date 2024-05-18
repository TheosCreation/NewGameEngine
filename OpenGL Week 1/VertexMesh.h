#pragma once
#include "Math.h"

class VertexMesh
{
public:
	VertexMesh() :m_position(), m_texcoord(), m_normal()
	{
	}
	VertexMesh(const  glm::vec3& position, const  glm::vec2& texcoord, const  glm::vec3& normal) :
		m_position(position),
		m_texcoord(texcoord),
		m_normal(normal)
	{
	}
	VertexMesh(const VertexMesh& vertex) :
		m_position(vertex.m_position),
		m_texcoord(vertex.m_texcoord),
		m_normal(vertex.m_normal)
	{
	}
public:
	glm::vec3 m_position;
	glm::vec2 m_texcoord;
	glm::vec3 m_normal;

};