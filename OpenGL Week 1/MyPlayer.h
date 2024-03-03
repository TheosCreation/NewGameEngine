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

	float m_camRotX = 0;
	float m_camRotY = 0;

	Camera* m_cam = nullptr;
};

