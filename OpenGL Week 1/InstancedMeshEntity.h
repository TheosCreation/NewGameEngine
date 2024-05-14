#pragma once

#include "GraphicsEntity.h"
#include <vector>

class InstancedMeshEntity : public GraphicsEntity
{
public:
	void setMesh(const MeshPtr& mesh);
	MeshPtr getMesh();

	virtual void setTexture(const TexturePtr& texture);
	TexturePtr getTexture();
	void setUniformData(UniformData data);
	virtual void onGraphicsUpdate(float deltaTime);
	void setShader(const ShaderPtr& shader);
	void addInstance(const glm::mat4& transform);
private:
	MeshPtr m_mesh;
	TexturePtr m_texture;
	std::vector<glm::mat4> m_instanceTransforms;
};