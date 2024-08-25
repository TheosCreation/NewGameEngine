#pragma once
#include "Utils.h"

class Framebuffer
{
public:
	Framebuffer(Rect _windowSize);
	~Framebuffer();

	uint GetRenderTexture();

	void Bind();
	void UnBind();

private:
	uint FBO;
	uint RBO;
	uint RenderTexture;
};

