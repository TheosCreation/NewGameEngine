#pragma once
#include "Entity.h"
#include "Mat4.h"
#include "Rect.h"

class EntitySystem;
//the GraphicsEntity class is the enity class of the entitysystem made specifically for graphcis objects
class GraphicsEntity : public Entity
{
public:
	GraphicsEntity();
	virtual ~GraphicsEntity();
	virtual void onGraphicsUpdate(float deltaTime) {}
protected:
	friend class EntitySystem;
};
