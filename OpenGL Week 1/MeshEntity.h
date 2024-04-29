/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : MeshEntity.h
Description : entity that create a mesh
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "GraphicsEntity.h"

class MeshEntity : public GraphicsEntity
{
public:
	void setMesh(const MeshPtr& mesh);
	MeshPtr getMesh();

	virtual void setTexture(const TexturePtr& texture);
	TexturePtr getTexture();
	void setUniformData(UniformData data);
	virtual void onGraphicsUpdate(float deltaTime);
	void setShader(const ShaderPtr& shader);
private:
	MeshPtr m_mesh;
	TexturePtr m_texture;
};
