#include "GraphicsEntity.h"

GraphicsEntity::GraphicsEntity()
{
}

GraphicsEntity::~GraphicsEntity()
{
}

ShaderPtr GraphicsEntity::getShader() const
{
	return m_shader;
}

void GraphicsEntity::setShader(const ShaderPtr& shader)
{
	m_shader = shader;
}

TexturePtr GraphicsEntity::getTexture() const
{
	return m_texture;
}

void GraphicsEntity::setTexture(const TexturePtr& texture)
{
	m_texture = texture;
}