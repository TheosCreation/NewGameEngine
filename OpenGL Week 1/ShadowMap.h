#pragma once
#include "Utils.h"
#include "Texture.h"
#include <glew.h>
#include <glfw3.h>

class ShadowMap : public Texture
{
public:
	ShadowMap(Vector2 _resoulution);
	~ShadowMap();

	virtual void Bind();
	virtual void Unbind();

private:
	uint FBO;
	Vector2 m_resolution = Vector2(0);
};

