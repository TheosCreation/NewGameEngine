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
protected:
	ShaderProgramPtr m_shader;
	TexturePtr m_texture;
	friend class EntitySystem;
};
