/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : GraphicsEntity.h
Description : entity to be rendered by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Entity.h"
#include "Rect.h"
#include "Texture.h"
#include "Shader.h"

class EntitySystem;
class GraphicsEntity : public Entity
{
public:
	GraphicsEntity();
	virtual ~GraphicsEntity();

	virtual void onGraphicsUpdate(float deltaTime) {}
	virtual void setUniformData(UniformData data) {};

	ShaderPtr getShader() const;
	void setShader(const ShaderPtr& shader);

	TexturePtr getTexture() const;
	void setTexture(const TexturePtr& texture);

protected:
	ShaderPtr m_shader;
	TexturePtr m_texture;
};
