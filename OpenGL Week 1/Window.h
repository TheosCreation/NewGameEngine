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
	void makeCurrentContext();
	void present(bool vsync);
	bool shouldClose();
private:
	std::shared_ptr<GLFWwindow> m_windowPtr;
	void* m_context = nullptr;
	Rect m_size = Rect(1024, 768);
};

