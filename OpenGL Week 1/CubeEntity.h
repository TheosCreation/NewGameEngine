#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

//the CubeEntity class is the entity class that allows to add a cube in the scene
class CubeEntity : public GraphicsEntity
{
public:
	virtual void onCreate();
	virtual void setTexture(const TexturePtr& texture);
	void setShader(const ShaderProgramPtr& shader);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
	ShaderProgramPtr m_shader;
	TexturePtr m_texture;
};