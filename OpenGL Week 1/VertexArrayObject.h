#pragma once
#include "Prerequisites.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& data);
	~VertexArrayObject();

	GLuint getId();
private:
	GLuint m_vertexBufferID = 0;
	GLuint m_vetexArrayObjectID = 0;
	VertexBufferDesc m_vertexBufferData;
};

