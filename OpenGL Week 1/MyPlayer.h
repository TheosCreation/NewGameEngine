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

	Camera* m_cam = nullptr;
};

