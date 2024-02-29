#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &m_vetexBufferID);

	glGenVertexArrays(1, &m_vetexArrayObjectID);
	glBindVertexArray(m_vetexArrayObjectID);

	glBindBuffer(GL_ARRAY_BUFFER, m_vetexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_vetexBufferID);
	glDeleteVertexArrays(1, &m_vetexArrayObjectID);
}

GLuint VertexArrayObject::getId()
{
	return m_vetexArrayObjectID;
}
