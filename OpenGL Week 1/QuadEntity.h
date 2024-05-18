/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : QuadEntity.h
Description : creates a quad with its texture split 4 times
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

class QuadEntity : public GraphicsEntity
{
public:
	virtual void onCreate();
	virtual void setUniformData(UniformData data);
	void setShader(const ShaderPtr& shader);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
};