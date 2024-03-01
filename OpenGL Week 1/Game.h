#pragma once
#include <iostream>
#include "GrapicsEngine.h"
#include "Prerequisites.h"
#include "VertexArrayObject.h"

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

	VertexArrayObjectPtr m_triangleVAO;
	//VertexArrayObjectPtr m_triangleVAO1;
};

