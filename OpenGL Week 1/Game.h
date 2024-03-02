#pragma once
#include <iostream>
#include <chrono>
#include "Prerequisites.h"
#include <glew.h>
#include <glfw3.h>
#include "Rect.h"

class GraphicsEngine;
class EntitySystem;
class Game
{
public:
	Game();
	virtual ~Game();

	void run();
	void quit();

	EntitySystem* getEntitySystem();

protected:
	virtual void onCreate();
	virtual void onUpdate(float deltaTime) {};
	virtual void onQuit();
private:
	void onUpdateInternal();

protected:
	bool m_isRunning = true;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	GLFWwindow* Window = nullptr;
	std::unique_ptr<EntitySystem> m_entitySystem;
	Rect displaySize = Rect(1000, 1000);

	VertexArrayObjectPtr m_polygonVAO;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shader;

	std::chrono::system_clock::time_point m_previousTime;
	float m_scale = 0;
};

