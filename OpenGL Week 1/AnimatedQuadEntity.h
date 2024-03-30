#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

class AnimatedQuadEntity : public GraphicsEntity
{
public:
	virtual void onCreate();
	virtual void setTexture(const TexturePtr& texture);
	virtual void setUniformData(UniformData data);
	void setShader(const ShaderProgramPtr& shader);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
	TexturePtr m_texture;
};