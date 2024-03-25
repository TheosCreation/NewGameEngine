#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

class HexagonEntity : public GraphicsEntity
{
public:


	virtual void onCreate();
	virtual void setTexture(const TexturePtr& texture);
	void setShader(const ShaderProgramPtr& shader);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shader;
	TexturePtr m_texture;
};

