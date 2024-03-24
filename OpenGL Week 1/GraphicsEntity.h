#pragma once
#include "Entity.h"
#include "Rect.h"

class EntitySystem;
class GraphicsEntity : public Entity
{
public:
	GraphicsEntity();
	virtual ~GraphicsEntity();
	virtual void onGraphicsUpdate(float deltaTime) {}
protected:
	friend class EntitySystem;
};
