#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& data)
{
	
	glGenVertexArrays(1, &m_vetexArrayObjectID);
	glBindVertexArray(m_vetexArrayObjectID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);

	for (unsigned int i = 0; i < data.attributesListSize; i++)
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

GLuint VertexArrayObject::getId()
{
	return m_vetexArrayObjectID;
}
