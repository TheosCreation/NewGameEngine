#pragma once

#include "GraphicsEntity.h"
#include <vector>

class InstancedMeshEntity : public GraphicsEntity
{
public:
	void setMesh(const InstancedMeshPtr& mesh);
	InstancedMeshPtr getMesh();

	virtual void setTexture(const TexturePtr& texture);
	TexturePtr getTexture();
	void setUniformData(UniformData data);
	virtual void onGraphicsUpdate(float deltaTime);
	void setShader(const ShaderPtr& shader);
private:
	InstancedMeshPtr m_mesh;
	TexturePtr m_texture;
};