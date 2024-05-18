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
#include "MyPlayer.h"

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
	MeshEntity* m_skybox = nullptr;
	MeshEntity* m_statue = nullptr;
	MeshEntity* m_ground = nullptr;
	InstancedMeshEntity* m_instancedTree = nullptr;
	MyPlayer* m_player = nullptr;
	QuadEntity* m_button = nullptr;

	float m_rotz = 0;
	float m_roty = 0;
	float m_uiScaleX = 2.0;
	float m_uiScaleY = -2.0;

};

