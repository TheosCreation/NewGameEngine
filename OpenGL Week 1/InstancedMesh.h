#pragma once

#include "Mesh.h"
#include "Math.h"
#include <vector>

class InstancedMesh : public Mesh {
public:
    InstancedMesh(const wchar_t* path, ResourceManager* manager);
    virtual ~InstancedMesh();

    void addInstance(glm::vec3 Position, glm::vec3 Scale, glm::vec3 Rotation);
    void initInstanceBuffer();

    int getInstanceCount();

private:
    std::vector<glm::mat4> m_instanceTransforms;
};