#pragma once

#include "Prerequisites.h"
#include "Vec2.h"
#include "Rect.h"
#include <glew.h>
#include <glfw3.h>

class Game;
class InputManager
{
public:

	InputManager();

	~InputManager();

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
	GLFWwindow* Window;
	short m_keys_state[256] = {};
	short m_old_keys_state[256] = {};
	short m_keys_state_res[256] = {};

	bool m_playEnable = false;
	Vec2 m_old_mouse_pos;
	bool m_first_time = true;
	Rect m_screenArea;
	Vec2 m_deltaMouse;
	int states_index = 0;
	Game* m_game = nullptr;

	friend class Game;
};

