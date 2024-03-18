#include "VertexArrayObject.h"
#include <iostream>
#include <glew.h>

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
{
	if (!data.listSize) OGL3D_ERROR("VertexArrayObject | listSize is NULL");
	if (!data.vertexSize) OGL3D_ERROR("VertexArrayObject | vertexSize is NULL");
	if (!data.verticesList) OGL3D_ERROR("VertexArrayObject | verticesList is NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	for (uint i = 0; i < data.attributesListSize; i++)
	{
		glVertexAttribPointer(
			i,
			data.attributesList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			data.vertexSize,
			(void*)((i == 0) ? 0 : data.attributesList[i - 1].numElements * sizeof(float))
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
	: VertexArrayObject(vbDesc)
{
	m_indexBufferDesc = ibDesc;

	if (!ibDesc.listSize) OGL3D_ERROR("VertexArrayObject | listSize is NULL");
	if (!ibDesc.indicesList) OGL3D_ERROR("VertexArrayObject | indicesList is NULL");

	glBindVertexArray(m_vertexArrayObjectID);

	glGenBuffers(1, &m_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_elementBufferId);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayObjectID);
}

uint VertexArrayObject::getId()
{
	return m_vertexArrayObjectID;
}

uint VertexArrayObject::getVertexBufferSize()
{
	return sizeof(m_vertexBufferData.vertexSize);
}

uint VertexArrayObject::getVertexSize()
{
	return uint();
}

uint VertexArrayObject::getNumIndices()
{
	return m_indexBufferDesc.listSize;
}