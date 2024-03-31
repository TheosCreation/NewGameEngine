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
	Entity* m_entity = nullptr;

	float m_camRotY = 0.0f;
	float m_camRotX = 0.0f;

	Camera* m_cam = nullptr;
};

