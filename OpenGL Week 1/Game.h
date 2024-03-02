#pragma once
#include <iostream>
#include <chrono>
#include "GrapicsEngine.h"
#include "Prerequisites.h"
#include "Rect.h"

class Game
{
public:
	Game();
	~Game();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	GrapicsEngine* m_graphicsEngine;
	GLFWwindow* Window = nullptr;
	Rect displaySize = Rect(1000, 1000);

	VertexArrayObjectPtr m_polygonVAO;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shader;

	std::chrono::system_clock::time_point m_previousTime;
	float m_scale = 0;
};

