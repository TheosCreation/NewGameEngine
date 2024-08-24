/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : InstancedMesh.cpp
Description : A class representing a instanced mesh resource
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "InstancedMesh.h"
#include "VertexArrayObject.h"

InstancedMesh::InstancedMesh(const char* path, ResourceManager* manager) : Mesh(path, manager)
{
}

InstancedMesh::~InstancedMesh()
{
}

void InstancedMesh::addInstance(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
    glm::mat4 transform = glm::identity<glm::mat4>();
    transform = glm::translate(transform, position);
    
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    transform = glm::scale(transform, scale);

    m_instanceTransforms.push_back(transform);
}

void InstancedMesh::initInstanceBuffer()
{
    getVertexArrayObject()->initInstanceBuffer(m_instanceTransforms.data(), m_instanceTransforms.size());
}

int InstancedMesh::getInstanceCount()
{
    return static_cast<int>(m_instanceTransforms.size());
}

void InstancedMesh::clearInstances()
{
	m_instanceTransforms.clear();
}