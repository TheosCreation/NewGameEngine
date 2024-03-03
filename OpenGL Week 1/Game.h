#pragma once
#include <iostream>
#include <chrono>
#include "Prerequisites.h"
#include "InputManager.h"
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
	GraphicsEngine* getGraphicsEngine();
	InputManager* getInputManager();
	GLFWwindow* getWindow();

protected:
	virtual void onCreate();
	virtual void onUpdate(float deltaTime) {};
	virtual void onGraphicsUpdate(float deltaTime);
	virtual void onQuit();
private:
	void onUpdateInternal();

protected:
	bool m_isRunning = true; 
	std::unique_ptr<GLFWwindow> Window = nullptr;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<EntitySystem> m_entitySystem;

	GLFWwindow* m_Window = nullptr;
	Window m_display = nullptr;
	Rect displaySize = Rect(1000, 1000);

	VertexArrayObjectPtr m_polygonVAO;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shader;

	std::chrono::system_clock::time_point m_previousTime;
	float m_scale = 0;

	friend class Entity;
};

