/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : AnimatedQuadEntity.h
Description : creates a quad with a animated texture
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

class AnimatedQuadEntity : public GraphicsEntity
{
public:
	virtual void onCreate();
	virtual void setTexture(const TexturePtr& texture);
	virtual void setUniformData(UniformData data);
	void setShader(const ShaderPtr& shader);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
	TexturePtr m_texture;
};