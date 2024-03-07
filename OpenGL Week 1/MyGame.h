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
	Entity* m_player = nullptr;

	float m_roty = 0;
	Entity* m_light = nullptr;
	Entity* m_lightred = nullptr;

	Entity* m_skybox = nullptr;

	ShaderProgramPtr m_meshShader;
	ShaderProgramPtr m_skyboxShader;
};

