/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : GraphicsEntity.cpp
Description : Entity type to be rendered by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

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

void GraphicsEntity::setColor(Vector3 color)
{
	m_color = color;
}