#pragma once
#include "All.h"

class MyGame : public Game
{
public:
	MyGame();
	~MyGame();

	virtual void onCreate();
	virtual void onUpdate(float deltaTime);

private:
	float m_elapsedSeconds = 0.0f;

	// init all vbo's here
	HexagonEntity* m_hexagon1 = nullptr;
	HexagonEntity* m_hexagon2 = nullptr;
	QuadEntity* m_quad1 = nullptr;
	AnimatedQuadEntity* m_quad2 = nullptr;

	float m_roty = 0;

};

