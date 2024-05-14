#pragma once

#include <map>
#include <string>
#include <vector>
#include "VertexArrayObject.h" 
#include "Utils.h"
#include "Mesh.h"

class InstancedMesh : public Mesh {
public:
    InstancedMesh(const wchar_t* path, ResourceManager* manager);
    ~InstancedMesh();

    VertexArrayObjectPtr getVertexArrayObject();

    void addInstance(glm::vec3 Position, glm::vec3 Scale, glm::vec3 Rotation);
    void updateInstanceBuffer();
    float getInstanceCount();

private:
    std::vector<glm::mat4> m_instanceTransforms;
    VertexArrayObjectPtr m_vao;
};