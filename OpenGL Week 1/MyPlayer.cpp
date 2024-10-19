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
    m_cam->setPosition(m_transform.position);

    m_uiCamera = getEntitySystem()->createEntity<Camera>();
    m_uiCamera->setCameraType(CameraType::Orthogonal);
}

void MyPlayer::onUpdate(float deltaTime)
{
    auto& inputManager = InputManager::GetInstance();
    auto& lightManager = LightManager::GetInstance();

    // Update the camera's position
    m_cam->setPosition(m_transform.position);

    float sensitivity = 0.1f;  // Sensitivity factor for mouse movement
    m_yaw -= inputManager.getMouseXAxis() * sensitivity;
    m_pitch -= inputManager.getMouseYAxis() * sensitivity;

    // Clamp the pitch value to prevent flipping the camera
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    // Create quaternions for yaw (around the y-axis) and pitch (around the x-axis)
    glm::quat yawRotation = glm::angleAxis(glm::radians(m_yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat pitchRotation = glm::angleAxis(glm::radians(m_pitch), glm::vec3(1.0f, 0.0f, 0.0f));

    // Combine yaw and pitch rotations
    glm::quat orientation = yawRotation * pitchRotation;

    // Update the camera's forward direction by rotating the default forward vector (0, 0, -1)
    Vector3 forward = glm::normalize(orientation * glm::vec3(0.0f, 0.0f, -1.0f));
    m_cam->setForwardDirection(forward);

    // Calculate the right and up vectors based on the new forward direction
    Vector3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    Vector3 up = glm::normalize(glm::cross(right, forward));
    m_cam->setUpwardDirection(up);

    // Combine this yaw rotation with the existing rotation
    m_transform.rotation = yawRotation * m_transform.rotation;

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


    //// Toggle directional light on/off
    //if (inputManager.isKeyPressed(Key::Key2))
    //{
    //    bool currentLightStatus = lightManager.getDirectionalLightStatus();
    //    lightManager.setDirectionalLightStatus(!currentLightStatus);
    //}

    //// Toggle spotlight on/off
    //if (inputManager.isKeyPressed(Key::Key3))
    //{
    //    bool currentLightStatus = lightManager.getSpotlightStatus();
    //    lightManager.setSpotlightStatus(!currentLightStatus);
    //}

    // Toggle wireframe mode on/off
    if (inputManager.isKeyPressed(Key::Key0))
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

    //// Get the mouse position from the input manager
    //glm::vec2 cursorPosition = inputManager.getMousePosition();

    //// Toggle to print the cords of the cursor
    //if (inputManager.isKeyPressed(Key::Key5))
    //{
    //    std::cout << "Mouse Coordinates: (" << cursorPosition.x << ", " << cursorPosition.y << ")" << std::endl;
    //}
    // Adjust camera speed if Shift key is pressed
    if (inputManager.isKeyDown(Key::KeyShift)) {
        m_movementSpeed = m_originalMovementSpeed * 2.0f;
    }
    else {
        m_movementSpeed = m_originalMovementSpeed;
    }

    if (inputManager.isKeyDown(Key::KeyW))
        m_transform.position += forward * m_movementSpeed * deltaTime;
    if (inputManager.isKeyDown(Key::KeyS))
        m_transform.position -= forward * m_movementSpeed * deltaTime;
    if (inputManager.isKeyDown(Key::KeyA))
        m_transform.position -= right * m_movementSpeed * deltaTime;
    if (inputManager.isKeyDown(Key::KeyD))
        m_transform.position += right * m_movementSpeed * deltaTime;

    // Handle input for player rotation
    if (inputManager.isKeyDown(Key::KeyQ))
        m_transform.position -= up * m_movementSpeed * deltaTime;
    if (inputManager.isKeyDown(Key::KeyE))
        m_transform.position += up * m_movementSpeed * deltaTime; glm::vec2 mouseScroll = inputManager.getMouseScroll();

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

void MyPlayer::onFixedUpdate(float fixedDeltaTime)
{
    // do physics here
}

void MyPlayer::onLateUpdate(float deltaTime)
{
}
