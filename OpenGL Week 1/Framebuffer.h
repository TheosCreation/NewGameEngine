#pragma once
#include "Utils.h"

class Framebuffer
{
public:
	Framebuffer(Rect _windowSize);
	~Framebuffer();

	void Bind();
	void UnBind();

	uint RenderTexture;
private:
	uint FBO;
	uint RBO;
};

