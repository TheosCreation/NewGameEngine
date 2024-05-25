/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : InputManager.h
Description : Handles inputs from the player/user of the program
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once

#include "Utils.h"
#include "Math.h"
#include "Rect.h"
#include <glew.h>
#include <glfw3.h>
#include <map>

/**
 * @class InputManager
 * @brief Handles inputs from the player/user of the program.
 */
class InputManager
{
public:
    /**
     * @brief Constructor for the InputManager class.
     */
    InputManager();

    /**
     * @brief Destructor for the InputManager class.
     */
    ~InputManager();

    /**
     * @brief Sets the game window for input handling.
     * @param window Pointer to the GLFW window.
     */
    void setGameWindow(GLFWwindow* window);

    /**
     * @brief Checks if the specified key is currently being held down.
     * @param key The key to check.
     * @return True if the key is down, false otherwise.
     */
    bool isKeyDown(Key key);

    /**
     * @brief Checks if the specified key was pressed.
     * @param key The key to check.
     * @return True if the key was pressed, false otherwise.
     */
    bool isKeyPressed(Key key);

    /**
     * @brief Checks if the specified key is currently not being held down.
     * @param key The key to check.
     * @return True if the key is up, false otherwise.
     */
    bool isKeyUp(Key key);

    /**
     * @brief Checks if the specified mouse button is currently being held down.
     * @param button The mouse button to check.
     * @return True if the mouse button is down, false otherwise.
     */
    bool isMouseDown(MouseButton button);

    /**
     * @brief Checks if the specified mouse button was pressed.
     * @param button The mouse button to check.
     * @return True if the mouse button was pressed, false otherwise.
     */
    bool isMousePressed(MouseButton button);

    /**
     * @brief Checks if the specified mouse button is currently not being held down.
     * @param button The mouse button to check.
     * @return True if the mouse button is up, false otherwise.
     */
    bool isMouseUp(MouseButton button);

    /**
     * @brief Returns the current mouse movement along the x-axis.
     * @return The mouse movement along the x-axis: -1 (left), 1 (right).
     */
    float getMouseXAxis();

    /**
     * @brief Returns the current mouse movement along the y-axis.
     * @return The mouse movement along the y-axis: -1 (bottom), 1 (top).
     */
    float getMouseYAxis();

    /**
     * @brief Returns the current mouse position as a vector2.
     * @return The current mouse position.
     */
    glm::vec2 getMousePosition();
    
    
    glm::vec2 getMouseScroll();

    /**
     * @brief Enables or disables play mode, which hides the cursor and locks it at the center of the screen.
     * @param enable True to enable play mode, false to disable.
     */
    void enablePlayMode(bool enable);

    /**
     * @brief Sets the screen area the cursor will be locked into when play mode is enabled.
     * @param area The screen area to set.
     */
    void setScreenArea(const Rect& area);

    /**
     * @brief Updates the input states.
     */
    void onUpdate(); 

    /**
     * @brief Update late after render.
     */
    void onLateUpdate();

private:
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    static double currentMouseX; //Current mouse x position
    static double currentMouseY; //Current mouse y position

    static double scrollX;
    static double scrollY;

    static std::map<Key, bool> currentKeyStates;
    static std::map<Key, bool> previousKeyStates;
    static std::map<MouseButton, bool> currentMouseStates;
    static std::map<MouseButton, bool> previousMouseStates;

    const double MOUSE_MOVEMENT_THRESHOLD = 0.0f;

    void resetMouseScroll();

    GLFWwindow* WindowPtr = nullptr; //Pointer to the GLFW window

    bool m_playEnable = false; //Indicates whether play mode is enabled
    glm::vec2 m_old_mouse_pos{}; //Previous mouse position
    Rect m_screenArea; //Screen area for cursor locking
    glm::vec2 m_deltaMouse{}; //Mouse movement delta

};