#include "InstancedMesh.h"

InstancedMesh::InstancedMesh(const wchar_t* path, ResourceManager* manager) : Mesh(path, manager)
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

size_t InstancedMesh::getInstanceCount()
{
    return m_instanceTransforms.size();
}