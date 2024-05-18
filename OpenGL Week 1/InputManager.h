/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : InputManager.h
Description : Handles inputs from the player/user of the program, not used in the program
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once

#include "Utils.h"
#include "Math.h"
#include "Rect.h"
#include <glew.h>
#include <glfw3.h>
#include <unordered_map>

constexpr int ARRAY_SIZE = GLFW_KEY_LAST;
class InputManager
{
public:

	InputManager();

	~InputManager();

	void SetGameWindow(GLFWwindow* window);

	// Checks if the specified key is currently being held down
	bool isKeyDown(Key key);

	// Checks if the specified key was pressed
	bool isKeyPressed(Key key);

	// Checks if the specified key is currently not being held down
	bool isKeyUp(Key key);

	// Checks if the specified mouse button is currently being held down
	bool isMouseDown(MouseButton button);

	// Checks if the specified mouse button was pressed
	bool isMousePressed(MouseButton button);

	// Checks if the specified mouse button is currently not being held down
	bool isMouseUp(MouseButton button);

	//getMouseXAxis returns the current mouse movement along x axis: -1 (left), 1 (right).
	float getMouseXAxis();

	//getMouseYAxis returns the current mouse movement along y axis: -1 (bottom), 1 (top).
	float getMouseYAxis();

	//getMousePosition returns the current mouse position as a vector2
	glm::vec2 getMousePosition();

	//enablePlayMode allows to hide the cursor and to lock it at the center of the screen.
	void enablePlayMode(bool enable);

	//setScreenArea allows to set the screen area the cursor will be locked into when playmode is enabled.
	void setScreenArea(const Rect& area);
	void update();

private:
	GLFWwindow* WindowPtr = nullptr;

	bool m_playEnable = false;
	glm::vec2 m_old_mouse_pos{};
	Rect m_screenArea;
	glm::vec2 m_deltaMouse{};

	double currentMouseX = 0.0f;
	double currentMouseY = 0.0f;

	//key states
	std::unordered_map<Key, bool> currentKeyStates;
	std::unordered_map<Key, bool> previousKeyStates;

	//mouse states
	std::unordered_map<MouseButton, bool> currentMouseStates;
	std::unordered_map<MouseButton, bool> previousMouseStates;
};

