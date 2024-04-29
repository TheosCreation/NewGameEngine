#pragma once
#include "GraphicsEntity.h"

class MeshEntity : public GraphicsEntity
{
public:
	MeshEntity();
	virtual ~MeshEntity();
public:
	void setMesh(const MeshPtr& mesh);
	MeshPtr getMesh();

	virtual void setTexture(const TexturePtr& texture);
	TexturePtr getTexture();
	virtual void onGraphicsUpdate(float deltaTime);
	void setShader(const ShaderPtr& shader);
	ShaderPtr getShader();
private:
	MeshPtr m_mesh;
	TexturePtr m_texture;
	ShaderPtr m_shader;
};

class MeshEntity
{
};

