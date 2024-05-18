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
	virtual void onCreate();
	virtual void setUniformData(UniformData data);
	virtual void onGraphicsUpdate(float deltaTime);
private:
	MeshPtr m_mesh;
};