#pragma once
#include <iostream>
#include "InputManager.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Rect.h"

class Window;
class EntitySystem;
class Game
{
public:
	Game();
	~Game();

	void run();
	void quit();

	EntitySystem* getEntitySystem();
	GraphicsEngine* getGraphicsEngine();
	InputManager* getInputManager();
	ResourceManager* getResourceManager();
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
	std::unique_ptr<ResourceManager> m_resourceManager;

	VertexArrayObjectPtr m_polygonVAO;

	float m_previousTime = 0;
	float m_currentTime = 0;
	float m_scale = 0;

	friend class Entity;
};

