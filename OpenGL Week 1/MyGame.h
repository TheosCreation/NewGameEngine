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
	MyPlayer* m_player = nullptr;
};

