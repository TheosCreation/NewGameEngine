#pragma once
#include "Utils.h"

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& data);
	VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	~VertexArrayObject();

	uint getId();
	uint getVertexBufferSize();
	uint getVertexSize();
	uint getNumIndices();
private:
	uint m_vertexBufferID = 0;
	uint m_elementBufferId = 0;
	uint m_vertexArrayObjectID = 0;
	VertexBufferDesc m_vertexBufferData;
	IndexBufferDesc m_indexBufferDesc;
};

