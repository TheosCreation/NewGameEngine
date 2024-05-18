/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : VertexMesh.h
Description : VertexMesh is a standard representation for a mesh vertex.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Math.h"

/**
 * @class VertexMesh
 * @brief A standard representation for a mesh vertex.
 */
class VertexMesh
{
public:
    /**
     * @brief Default constructor for the VertexMesh class.
     */
    VertexMesh() : m_position(), m_texcoord(), m_normal()
    {
    }

    /**
     * @brief Constructor for the VertexMesh class with position, texture coordinate, and normal.
     * @param position The position of the vertex.
     * @param texcoord The texture coordinate of the vertex.
     * @param normal The normal vector of the vertex.
     */
    VertexMesh(const glm::vec3& position, const glm::vec2& texcoord, const glm::vec3& normal) :
        m_position(position),
        m_texcoord(texcoord),
        m_normal(normal)
    {
    }

    /**
     * @brief Copy constructor for the VertexMesh class.
     * @param vertex The vertex to copy.
     */
    VertexMesh(const VertexMesh& vertex) :
        m_position(vertex.m_position),
        m_texcoord(vertex.m_texcoord),
        m_normal(vertex.m_normal)
    {
    }

public:
    glm::vec3 m_position; //The position of the vertex.
    glm::vec2 m_texcoord; //The texture coordinate of the vertex.
    glm::vec3 m_normal; //The normal vector of the vertex.
};