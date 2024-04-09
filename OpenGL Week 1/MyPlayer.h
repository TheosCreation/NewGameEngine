/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : MyPlayer.h
Description : MyPlayer class is a entity that can be adjusted by the user
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"

class MyPlayer : public Entity
{
public:
	MyPlayer();
	~MyPlayer();

	virtual void onCreate();
	virtual void onUpdate(float deltaTime);

private:
	float m_elapsedSeconds = 0.0f;
	Entity* m_entity = nullptr;

	float m_zoomSpeed = 5.0f;
	float m_orbitSpeed = 5.0f;
	float m_orbitHorizontal = 0.0f;
	float m_minimumOrbitalRadius = 5.0f;
	float m_maximumOrbitalRadius = 30.0f;
	float m_orbitRadius = 10.0f;
	float m_inactivityTimer = 1.0f;

	Camera* m_cam = nullptr;
};

