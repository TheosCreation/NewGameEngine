#pragma once

#include <vector>
#include "VertexArrayObject.h"
#include "Math.h"
#include "Mesh.h"

class InstancedMesh : public Mesh {
public:
    InstancedMesh(const wchar_t* path, ResourceManager* manager);
    virtual ~InstancedMesh();

    void addInstance(glm::vec3 Position, glm::vec3 Scale, glm::vec3 Rotation);
    void updateInstanceBuffer();
    uint getInstanceCount();

    glm::mat4 m_instanceTransforms[1000];
private:
    uint instanceCount = 0;
};