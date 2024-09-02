#pragma once
#include "Utils.h"
#include <glew.h>
#include <glfw3.h>

class ShadowMap
{
public:
	ShadowMap(Vector2 _windowSize);
	~ShadowMap();

	virtual void Bind();
	virtual void Unbind();

	void resize(Vector2 _newWindowSize);

	const uint GetShadowTexture() const { return ShadowTexture; };

private:
	uint FBO;
	uint ShadowTexture;
};

