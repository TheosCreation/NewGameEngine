#include "InstancedMesh.h"

InstancedMesh::InstancedMesh(const wchar_t* path, ResourceManager* manager) : Mesh(path, manager)
{
    // Initialize instance buffer
    m_instanceTransforms.reserve(100);
}

InstancedMesh::~InstancedMesh()
{
}

void InstancedMesh::addInstance(glm::vec3 Position, glm::vec3 Scale = glm::vec3(1.0f), glm::vec3 Rotation = glm::vec3(1.0f))
{
    glm::mat4 transform = glm::mat4(1.0f); // Identity matrix
    transform = glm::translate(transform, position); // Apply translation
    transform = glm::scale(transform, scale);

    m_instanceTransforms.push_back(transform);
}

void InstancedMesh::updateInstanceBuffer()
{
    auto vao = getVertexArrayObject();
    vao->updateInstanceBuffer(m_instanceTransforms.data(), m_instanceTransforms.size());
}