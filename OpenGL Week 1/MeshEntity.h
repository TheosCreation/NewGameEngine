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
private:
	MeshPtr m_mesh;
	TexturePtr m_texture;
};

