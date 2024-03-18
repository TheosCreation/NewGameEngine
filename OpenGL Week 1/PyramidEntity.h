#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

//the PyramidEntity class is the entity class that allows to add a pyramid in the scene
class PyramidEntity : public GraphicsEntity
{
public:


	virtual void onCreate();
	virtual void setTexture(const TexturePtr& texture);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shaderProgram;
	TexturePtr m_texture;
};

