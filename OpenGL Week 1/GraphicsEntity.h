#pragma once
#include "Entity.h"
#include "Rect.h"
#include "Texture.h"
#include "ShaderProgram.h"

class EntitySystem;
class GraphicsEntity : public Entity
{
public:
	GraphicsEntity();
	virtual ~GraphicsEntity();
	ShaderProgramPtr getShader();

	void setShader(const ShaderProgramPtr& shader);

	virtual void onGraphicsUpdate(float deltaTime) {}
protected:
	ShaderProgramPtr m_shader;
	TexturePtr m_texture;
	friend class EntitySystem;
};
