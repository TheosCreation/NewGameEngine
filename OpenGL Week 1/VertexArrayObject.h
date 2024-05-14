/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : VertexArrayObject.h
Description : VertexArrayObject class is a representation of a VAO to be used by the graphics engine class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& data);
	VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	~VertexArrayObject();

	void updateInstanceBuffer(const glm::mat4* instanceData, size_t instanceCount);

	uint getId();
	uint getVertexBufferSize();
	uint getVertexSize();
	uint getNumIndices();
private:
	uint m_vertexBufferID = 0;
	uint m_elementBufferId = 0;
	uint m_vertexArrayObjectID = 0;
	uint m_instanceBufferID = 0;
	VertexBufferDesc m_vertexBufferData;
	IndexBufferDesc m_indexBufferDesc;
};