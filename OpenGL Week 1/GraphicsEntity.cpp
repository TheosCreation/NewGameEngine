#include "GraphicsEntity.h"

GraphicsEntity::GraphicsEntity()
{
}

GraphicsEntity::~GraphicsEntity()
{
}

ShaderProgramPtr GraphicsEntity::getShader()
{
	return m_shader;
}
