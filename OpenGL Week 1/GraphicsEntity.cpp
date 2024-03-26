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

void GraphicsEntity::setShader(const ShaderProgramPtr& shader)
{
    m_shader = shader;
}