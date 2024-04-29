/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : MyGame.h
Description : MyGame class is a stripped down class of the base game class to be able for users to create thier own entities
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

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
	MeshEntity* m_skybox = nullptr;

	float m_rotz = 0;
	float m_roty = 0;

};

