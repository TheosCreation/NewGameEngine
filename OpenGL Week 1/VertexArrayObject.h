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

	uint getId();
	int getVertexBufferSize();
private:
	uint m_vertexBufferID = 0;
	uint m_vetexArrayObjectID = 0;
	VertexBufferDesc m_vertexBufferData;
};

