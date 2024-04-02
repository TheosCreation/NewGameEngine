#include "GraphicsEntity.h"

GraphicsEntity::GraphicsEntity()
{
}

GraphicsEntity::~GraphicsEntity()
{
}

ShaderPtr GraphicsEntity::getShader()
{
	return m_shader;
}
