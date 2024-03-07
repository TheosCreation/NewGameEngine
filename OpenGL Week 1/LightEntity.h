#pragma once
#include "Utils.h"
#include "Entity.h"
#include "Math.h"

class Game;
class LightEntity : public Entity
{
public:
	LightEntity();
	virtual ~LightEntity();
public:
	void setColor(const glm::vec4& color);
	glm::vec4 getColor();
private:
	glm::vec4 m_color = glm::vec4(1, 1, 1, 1);

	friend class  Game;
};

