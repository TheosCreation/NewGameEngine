#pragma once
#include "GraphicsEntity.h"
#include "Rect.h"

class HexagonEntity : public GraphicsEntity
{
public:


	virtual void onCreate();
	virtual void setTexture(const TexturePtr& texture);
protected:
	virtual void onGraphicsUpdate(float deltaTime);

private:
	VertexArrayObjectPtr m_mesh;
	ShaderProgramPtr m_shader;
	TexturePtr m_texture;
};

