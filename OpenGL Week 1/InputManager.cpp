#include "InputManager.h"
#include "Game.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::SetGameWindow(GLFWwindow* window)
{
	WindowPtr = window;
}

bool InputManager::isKeyDown(Key key)
{
	int keyGLFW = GLFW_KEY_UNKNOWN;

	if (key >= KeyA && key <= KeyZ)
		keyGLFW = GLFW_KEY_A + (key - KeyA);
	else if (key >= Key0 && key <= Key9)
		keyGLFW = GLFW_KEY_0 + (key - Key0);
	else if (key == KeyShift)
		keyGLFW = GLFW_KEY_LEFT_SHIFT;
	else if (key == KeyEscape)
		keyGLFW = GLFW_KEY_ESCAPE;
	
	return (glfwGetKey(WindowPtr, keyGLFW) == GLFW_PRESS);
}

bool InputManager::isKeyUp(Key key)
{
	int keyGLFW = GLFW_KEY_UNKNOWN;

	if (key >= KeyA && key <= KeyZ)
		keyGLFW = GLFW_KEY_A + (key - KeyA);
	else if (key >= Key0 && key <= Key9)
		keyGLFW = GLFW_KEY_0 + (key - Key0);
	else if (key == KeyShift)
		keyGLFW = GLFW_KEY_LEFT_SHIFT;
	else if (key == KeyEscape)
		keyGLFW = GLFW_KEY_ESCAPE;

	return (glfwGetKey(WindowPtr, keyGLFW) == GLFW_PRESS);
}

bool InputManager::isMouseDown(MouseButton button)
{
	int buttonGLFW = -1;

	if (button == MouseButtonLeft)
		buttonGLFW = GLFW_MOUSE_BUTTON_LEFT;
	else if (button == MouseButtonMiddle)
		buttonGLFW = GLFW_MOUSE_BUTTON_MIDDLE;
	else if (button == MouseButtonRight)
		buttonGLFW = GLFW_MOUSE_BUTTON_RIGHT;

	if (buttonGLFW != -1) {
		return (glfwGetMouseButton(WindowPtr, buttonGLFW) == GLFW_PRESS);
	}

	return false;
}

bool InputManager::isMouseUp(MouseButton button)
{
	int buttonGLFW = -1;

	if (button == MouseButtonLeft)
		buttonGLFW = GLFW_MOUSE_BUTTON_LEFT;
	else if (button == MouseButtonMiddle)
		buttonGLFW = GLFW_MOUSE_BUTTON_MIDDLE;
	else if (button == MouseButtonRight)
		buttonGLFW = GLFW_MOUSE_BUTTON_RIGHT;

	if (buttonGLFW != -1) {
		return (glfwGetMouseButton(WindowPtr, buttonGLFW) == GLFW_RELEASE);
	}

	return false;
}

float InputManager::getMouseXAxis()
{
	return m_deltaMouse.x;
}

float InputManager::getMouseYAxis()
{
	return m_deltaMouse.y;
}

void InputManager::enablePlayMode(bool enable)
{
	m_playEnable = enable;

	if (enable) {
		glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void InputManager::setScreenArea(const Rect& area)
{
	m_screenArea = area;
}

void InputManager::update()
{
	double currentMouseX, currentMouseY;
	glfwGetCursorPos(WindowPtr, &currentMouseX, &currentMouseY);

	const double MOUSE_MOVEMENT_THRESHOLD = 0.01;

	if (std::abs(currentMouseX - m_old_mouse_pos.x) > MOUSE_MOVEMENT_THRESHOLD || std::abs(currentMouseY - m_old_mouse_pos.y) > MOUSE_MOVEMENT_THRESHOLD)
	{
		m_deltaMouse = Vec2((float)(currentMouseX - m_old_mouse_pos.x), (float)(currentMouseY - m_old_mouse_pos.y));
	}
	else
	{
		m_deltaMouse = Vec2(0, 0);
	}

	if (!m_playEnable)
	{
		m_old_mouse_pos = Vec2((float)currentMouseX, (float)currentMouseY);
	}
	else
	{
		Vec2 center_screen = Vec2(m_screenArea.left + (float)m_screenArea.width / 2.0f, m_screenArea.top + (float)m_screenArea.height / 2.0f);
		glfwSetCursorPos(WindowPtr, center_screen.x, center_screen.y);
		m_old_mouse_pos = center_screen;
	}

	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		int keyState = glfwGetKey(WindowPtr, i);

		if (keyState == GLFW_PRESS)
		{
			m_keys_state_res[i] = 0;
		}
		else // KEY IS UP
		{
			if (keyState != m_old_keys_state[i])
			{
				m_keys_state_res[i] = 1;
			}
			else
			{
				m_keys_state_res[i] = 2;
			}
		}
	}

	std::memcpy(m_old_keys_state, m_keys_state_res, sizeof(int) * std::min(GLFW_KEY_LAST, ARRAY_SIZE));
}
