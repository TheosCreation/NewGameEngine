#include "LightEntity.h"

LightEntity::LightEntity()
{
}

LightEntity::~LightEntity()
{
}

void LightEntity::setColor(const glm::vec4& color)
{
    m_color = color;
}

glm::vec4 LightEntity::getColor()
{
    return m_color;
}
