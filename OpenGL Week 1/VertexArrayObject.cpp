/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : VertexArrayObject.cpp
Description : VertexArrayObject class is a representation of a VAO to be used by the graphics engine class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "VertexArrayObject.h"
#include <glew.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
{
	if (!data.listSize) Debug::LogError("VertexArrayObject | vertexBuffer.listSize is NULL");
	if (!data.vertexSize) Debug::LogError("VertexArrayObject | vertexBuffer.vertexSize is NULL");
	if (!data.verticesList) Debug::LogError("VertexArrayObject | vertexBuffer.verticesList is NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	//init vertex buffer
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	size_t offset = 0;
	for (uint i = 0; i < data.attributesListSize; i++)
	{
		offset += ((i == 0) ? 0 : data.attributesList[i - 1].numElements * sizeof(float));

		glVertexAttribPointer(
			i,
			data.attributesList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			data.vertexSize,
			(void*)offset
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
	: VertexArrayObject(vbDesc)
{

	if (!ibDesc.listSize) Debug::LogError("VertexArrayObject | indexBuffer.listSize is NULL");
	if (!ibDesc.indicesList) Debug::LogError("VertexArrayObject | indexBuffer.indicesList is NULL");
	
	glBindVertexArray(m_vertexArrayObjectID);

	//init index buffer
	glGenBuffers(1, &m_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize * sizeof(uint), ibDesc.indicesList, GL_STATIC_DRAW);
	glBindVertexArray(0);
	m_indexBufferDesc = ibDesc;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_elementBufferId);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayObjectID);
}

void VertexArrayObject::initInstanceBuffer(Mat4* instanceData, size_t instanceCount)
{
	glBindVertexArray(m_vertexArrayObjectID);

	//init instance buffer
	glGenBuffers(1, &m_instanceBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBufferID);
	glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(Mat4), instanceData, GL_DYNAMIC_DRAW);

	// instance data is bound to attribute locations 3, 4, and 5, 6
	for (int i = 0; i < 4; i++) {
		glEnableVertexAttribArray(3 + i);
		glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (void*)(sizeof(glm::vec4) * i));
		glVertexAttribDivisor(3 + i, 1);
	}

	glBindVertexArray(0);
}

uint VertexArrayObject::getId()
{
	return m_vertexArrayObjectID;
}

uint VertexArrayObject::getVertexBufferSize()
{
	return sizeof(m_vertexBufferData.vertexSize);
}

uint VertexArrayObject::getNumIndices()
{
	return m_indexBufferDesc.listSize;
}
