#pragma once
#include <memory>

class VertexArrayObject;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;

struct VertexBufferData
{
	void* verticesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;

};
