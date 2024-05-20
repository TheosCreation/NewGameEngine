#include "LightManager.h"
#include "Shader.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::applyLighting(ShaderPtr shader)
{
	shader->setFloat("AmbientStrength", AmbientStrength);
	shader->setVec3("AmbientColor", AmbientColor);
	shader->setVec3("LightColor", LightColor);
	shader->setVec3("LightPos", LightPos);
	shader->setFloat("LightSpecularStrength", LightSpecularStrength);
}