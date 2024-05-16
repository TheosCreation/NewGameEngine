#include "InputManager.h"

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
	else if (key == KeyLeft)
		keyGLFW = GLFW_KEY_LEFT;
	else if (key == KeyRight)
		keyGLFW = GLFW_KEY_RIGHT;
	else if (key == KeyUp)
		keyGLFW = GLFW_KEY_UP;
	else if (key == KeyDown)
		keyGLFW = GLFW_KEY_DOWN;

	return (glfwGetKey(WindowPtr, keyGLFW) == GLFW_PRESS);
}

bool InputManager::isKeyPressed(Key key)
{
	return !previousKeyStates[key] && currentKeyStates[key];
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
	else if (key == KeyLeft)
		keyGLFW = GLFW_KEY_LEFT;
	else if (key == KeyRight)
		keyGLFW = GLFW_KEY_RIGHT;
	else if (key == KeyUp)
		keyGLFW = GLFW_KEY_UP;
	else if (key == KeyDown)
		keyGLFW = GLFW_KEY_DOWN;

	return (glfwGetKey(WindowPtr, keyGLFW) == GLFW_RELEASE);
}

bool InputManager::isMouseDown(MouseButton button)
{
	int buttonGLFW = -1;

	switch (button) {
	case MouseButton::MouseButtonLeft:
		buttonGLFW = GLFW_MOUSE_BUTTON_LEFT;
		break;
	case MouseButton::MouseButtonMiddle:
		buttonGLFW = GLFW_MOUSE_BUTTON_MIDDLE;
		break;
	case MouseButton::MouseButtonRight:
		buttonGLFW = GLFW_MOUSE_BUTTON_RIGHT;
		break;
	default:
		break;
	}

	if (buttonGLFW != -1) {
		return (glfwGetMouseButton(WindowPtr, buttonGLFW) == GLFW_PRESS);
	}

	return false;
}

bool InputManager::isMouseUp(MouseButton button)
{
	int buttonGLFW = -1;

	switch (button) {
	case MouseButton::MouseButtonLeft:
		buttonGLFW = GLFW_MOUSE_BUTTON_LEFT;
		break;
	case MouseButton::MouseButtonMiddle:
		buttonGLFW = GLFW_MOUSE_BUTTON_MIDDLE;
		break;
	case MouseButton::MouseButtonRight:
		buttonGLFW = GLFW_MOUSE_BUTTON_RIGHT;
		break;
	default:
		break;
	}

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

glm::vec2 InputManager::getCursorPosition()
{
	double mouseX, mouseY;
	glfwGetCursorPos(WindowPtr, &mouseX, &mouseY);
	glm::vec2 currentCursorPosition(mouseX, mouseY);
	return currentCursorPosition;
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
		m_deltaMouse = glm::vec2((float)(currentMouseX - m_old_mouse_pos.x), (float)(currentMouseY - m_old_mouse_pos.y));
	}
	else
	{
		m_deltaMouse = glm::vec2(0, 0);
	}

	if (!m_playEnable)
	{
		m_old_mouse_pos = glm::vec2((float)currentMouseX, (float)currentMouseY);
	}
	else
	{
		glm::vec2 center_screen = glm::vec2(m_screenArea.left + (float)m_screenArea.width / 2.0f, m_screenArea.top + (float)m_screenArea.height / 2.0f);
		glfwSetCursorPos(WindowPtr, center_screen.x, center_screen.y);
		m_old_mouse_pos = center_screen;
	}

	// Update the previous key states to the current key states
	previousKeyStates = currentKeyStates;

	// Update the current key states
	for (auto& keyState : currentKeyStates) {
		keyState.second = isKeyDown(keyState.first);
	}
}
