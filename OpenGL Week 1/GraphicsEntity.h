#pragma once
#include "Entity.h"
#include "Mat4.h"
#include "Rect.h"

class Game;
//the GraphicsEntity class is the enity class of the entitysystem made specifically for graphcis objects
class GraphicsEntity : public Entity
{
public:
	GraphicsEntity();
	virtual ~GraphicsEntity();
protected:
	virtual void onGraphicsUpdate(float deltaTime) {}
	friend class Game;
};
