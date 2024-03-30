#include "Texture2D.h"
#include <glew.h>

Texture2D::Texture2D(const Texture2DDesc& desc)
{
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	auto glChannels = GL_RGB;
	if (desc.numChannels == 3) glChannels = GL_RGB;
	else if (desc.numChannels == 4) glChannels = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, desc.textureSize.width, desc.textureSize.height, 0, glChannels, GL_UNSIGNED_BYTE, desc.textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	m_desc = desc;
}
void Texture2D::setMirrored()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}
Texture2D::~Texture2D()
{
}

uint Texture2D::getId()
{
	return m_textureId;
}
