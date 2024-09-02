#pragma once
#include "Utils.h"

class Framebuffer
{
public:
	Framebuffer(Vector2 _windowSize);
	~Framebuffer();

	void resize(Vector2 _newWindowSize);
	void Bind();
	void UnBind();

	uint RenderTexture;
private:
	uint FBO;
	uint RBO;
};

