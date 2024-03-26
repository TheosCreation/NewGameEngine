#pragma once
#include <memory>

#include <glew.h>
#include <glfw3.h>
#include "Rect.h"

class Window
{
public:
	Window();
	~Window();

	Rect getInnerSize();
	GLFWwindow* getWindow();
	void makeCurrentContext(bool vsync);
	void present();
	bool shouldClose();
private:
	GLFWwindow* m_windowPtr;
	void* m_context = nullptr;
	Rect m_size = Rect(800, 800);
};

