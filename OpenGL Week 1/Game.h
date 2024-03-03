#pragma once
#include <iostream>
#include <chrono>
#include "Prerequisites.h"
#include "InputManager.h"
#include "GraphicsEngine.h"
#include "Entity.h"
#include "Rect.h"

class Window;
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
	Window* getWindow();

protected:
	virtual void onCreate();
	virtual void onUpdate(float deltaTime) {};
	virtual void onGraphicsUpdate(float deltaTime);
	virtual void onQuit();
private:
	void onUpdateInternal();

protected:
	bool m_isRunning = true; 
	std::unique_ptr<Window> m_display;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<EntitySystem> m_entitySystem;

	VertexArrayObjectPtr m_polygonVAO;
	UniformBufferPtr m_uniform;
	ShaderProgramPtr m_shader;

	std::chrono::system_clock::time_point m_previousTime;
	float m_scale = 0;

	friend class Entity;
};

