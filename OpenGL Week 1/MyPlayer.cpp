/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : MyPlayer.cpp
Description : MyPlayer class is an entity that can be adjusted by the end user
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "MyPlayer.h"
#include <algorithm>

MyPlayer::MyPlayer()
{
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{
	m_cam = getEntitySystem()->createEntity<Camera>();
    m_cam->setPosition(m_position);

    m_uiCamera = getEntitySystem()->createEntity<Camera>();
    m_uiCamera->setCameraType(CameraType::Orthogonal);
}

void MyPlayer::onUpdate(float deltaTime)
{
    auto& inputManager = InputManager::GetInstance();
    // Update the camera's position
    m_cam->setPosition(m_position);

    float sensitivity = 0.1f;  // Sensitivity factor for mouse movement
    m_yaw += inputManager.getMouseXAxis() * sensitivity;
    m_pitch -= inputManager.getMouseYAxis() * sensitivity;

    // Clamp the pitch value to prevent flipping the camera
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    // Update the camera's forward direction based on yaw and pitch
    Vector3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    Vector3 forward = glm::normalize(direction);
    m_cam->setForwardDirection(forward);

    // Calculate the right and up vectors
    Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 right = m_cam->getRightwardDirection();
    Vector3 up = glm::normalize(glm::cross(right, forward));
    m_cam->setUpwardDirection(up);

    m_rotation.y = glm::radians(-m_yaw);
}

void MyPlayer::onFixedUpdate(float fixedDeltaTime)
{
    auto& inputManager = InputManager::GetInstance();
    auto& lightManager = LightManager::GetInstance();

    Vector3 forward = m_cam->getForwardDirection();
    Vector3 up = m_cam->getUpwardDirection();
    Vector3 right = m_cam->getRightwardDirection();

    // Enable play mode when clicking on the window
    if (inputManager.isMousePressed(MouseButtonLeft) && !m_playMode)
    {
        m_playMode = true;
        inputManager.enablePlayMode(m_playMode);
    }

    // Disable play mode when pressing the Escape key
    if (inputManager.isKeyPressed(Key::KeyEscape) && m_playMode)
    {
        m_playMode = false;
        inputManager.enablePlayMode(m_playMode);
    }

    //// Toggle point lights on/off
    //if (inputManager.isKeyPressed(Key::Key1))
    //{
    //    bool currentLightStatus = lightManager.getPointLightsStatus();
    //    lightManager.setPointLightsStatus(!currentLightStatus);
    //}
    

    // Toggle directional light on/off
    if (inputManager.isKeyPressed(Key::Key2))
    {
        bool currentLightStatus = lightManager.getDirectionalLightStatus();
        lightManager.setDirectionalLightStatus(!currentLightStatus);
    }

    // Toggle spotlight on/off
    if (inputManager.isKeyPressed(Key::Key3))
    {
        bool currentLightStatus = lightManager.getSpotlightStatus();
        lightManager.setSpotlightStatus(!currentLightStatus);
    }

    // Toggle wireframe mode on/off
    if (inputManager.isKeyPressed(Key::Key4))
    {
        m_wireframeMode = !m_wireframeMode;
        if (m_wireframeMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }

    // Get the mouse position from the input manager
    glm::vec2 cursorPosition = inputManager.getMousePosition();

    // Toggle to print the cords of the cursor
    if (inputManager.isKeyPressed(Key::Key5))
    {
        std::cout << "Mouse Coordinates: (" << cursorPosition.x << ", " << cursorPosition.y << ")" << std::endl;
    }


    // Adjust camera speed if Shift key is pressed
    if (inputManager.isKeyDown(Key::KeyShift)) {
        m_movementSpeed = m_originalMovementSpeed * 2.0f;
    }
    else {
        m_movementSpeed = m_originalMovementSpeed;
    }

    if (inputManager.isKeyDown(Key::KeyW))
        m_position += forward * m_movementSpeed * fixedDeltaTime;
    if (inputManager.isKeyDown(Key::KeyS))
        m_position -= forward * m_movementSpeed * fixedDeltaTime;
    if (inputManager.isKeyDown(Key::KeyA))
        m_position -= right * m_movementSpeed * fixedDeltaTime;
    if (inputManager.isKeyDown(Key::KeyD))
        m_position += right * m_movementSpeed * fixedDeltaTime;

    // Handle input for player rotation
    if (inputManager.isKeyDown(Key::KeyQ))
        m_position -= up * m_movementSpeed * fixedDeltaTime;
    if (inputManager.isKeyDown(Key::KeyE))
        m_position += up * m_movementSpeed * fixedDeltaTime;glm::vec2 mouseScroll = inputManager.getMouseScroll();

    if (mouseScroll.y < 0 || mouseScroll.y > 0)
    {
        m_fov -= mouseScroll.y * m_zoomSpeed;

        // Clamp the FOV to prevent it from going out of a reasonable range
        if (m_fov < m_minFov) {
            m_fov = m_minFov;
        }
        if (m_fov > m_maxFov) {
            m_fov = m_maxFov;
        }
        m_cam->setFieldOfView(m_fov);
    }

}

void MyPlayer::onLateUpdate(float deltaTime)
{
}
