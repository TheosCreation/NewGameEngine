#pragma once
#include "Utils.h"
#include "Texture.h"
#include <glew.h>
#include <glfw3.h>

class ShadowMap : public Texture
{
public:
	ShadowMap(Vector2 _windowSize);
	~ShadowMap();

	virtual void Bind();
	virtual void Unbind();

	void resize(Vector2 _newWindowSize);

private:
	uint FBO;
};

