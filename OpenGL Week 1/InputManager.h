#pragma once

#include "Utils.h"
#include "Math.h"
#include "Rect.h"
#include <glew.h>
#include <glfw3.h>

constexpr int ARRAY_SIZE = GLFW_KEY_LAST;
class InputManager
{
public:

	InputManager();

	~InputManager();

	void SetGameWindow(GLFWwindow* window);

	bool isKeyDown(Key key);

	bool isKeyUp(Key key);

	bool isMouseDown(MouseButton button);

	bool isMouseUp(MouseButton button);

	//getMouseXAxis returns the current mouse movement along x axis: -1 (left), 1 (right).
	float getMouseXAxis();
	//getMouseYAxis returns the current mouse movement along y axis: -1 (bottom), 1 (top).
	float getMouseYAxis();

	//enablePlayMode allows to hide the cursor and to lock it at the center of the screen.
	void enablePlayMode(bool enable);

	//setScreenArea allows to set the screen area the cursor will be locked into when playmode is enabled.
	void setScreenArea(const Rect& area);
	void update();

private:
	GLFWwindow* WindowPtr = nullptr;

	bool m_playEnable = false;
	glm::vec2 m_old_mouse_pos;
	Rect m_screenArea;
	glm::vec2 m_deltaMouse;
};

