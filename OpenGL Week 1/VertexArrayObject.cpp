#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
{
	if (!data.listSize) OGL3D_ERROR("VertexArrayObject | listSize is NULL");
	if (!data.vertexSize) OGL3D_ERROR("VertexArrayObject | vertexSize is NULL");
	if (!data.verticesList) OGL3D_ERROR("VertexArrayObject | verticesList is NULL");

	glGenVertexArrays(1, &m_vetexArrayObjectID);
	glBindVertexArray(m_vetexArrayObjectID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	for (uint i = 0; i < data.attributesListSize; i++)
	{
		glVertexAttribPointer(
			i, 
			data.attributesList[1].numElements,
			GL_FLOAT, 
			GL_FALSE,
			data.vertexSize, 
			(void*)((i==0)?0: data.attributesList[i-1].numElements*sizeof(float))
		);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vetexArrayObjectID);
}

uint VertexArrayObject::getId()
{
	return m_vetexArrayObjectID;
}

int VertexArrayObject::getVertexBufferSize()
{
	return sizeof(m_vertexBufferData.vertexSize);
}
