#pragma once
#include "Prerequisites.h"
#include <glew.h>
#include <glfw3.h>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferData& data);
	~VertexArrayObject();

	GLuint getId();
private:
	GLuint m_vetexBufferID = 0;
	GLuint m_vetexArrayObjectID = 0;
};

