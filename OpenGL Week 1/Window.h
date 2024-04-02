/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Window.h
Description : Window class is a wrapper of a GLFWwindow to display the rendering from the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

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