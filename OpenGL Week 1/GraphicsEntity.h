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

	virtual void onGraphicsUpdate(float deltaTime) {}

	ShaderProgramPtr getShader();

	virtual void setUniformData(UniformData data) {};
protected:
	ShaderProgramPtr m_shader;
	friend class EntitySystem;
};
