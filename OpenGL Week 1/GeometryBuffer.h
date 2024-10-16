#pragma once
#include "Utils.h"

class Shader;

class GeometryBuffer
{
public:
	GeometryBuffer(Vector2 _windowSize);
	~GeometryBuffer();

	void Bind();
	void UnBind();

	void PopulateShader(Shader _shader);
	void Resize(Vector2 _windowSize);

private:
	Vector2 m_size = Vector2(0.0f);
	uint FBO;

	uint Texture_Position;
	uint Texture_Normal;
	uint Texture_AlbedoShininess;
	uint Texture_Depth;
};

