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
    m_cam->setPosition(m_position + m_playerHeightOffset);

    m_uiCamera = getEntitySystem()->createEntity<Camera>();
    m_uiCamera->setCameraType(CameraType::Orthogonal);
    input = getGame()->getInputManager();
    lighting = getGame()->getLightingManager();
}

void MyPlayer::onUpdate(float deltaTime)
{
    // Enable play mode when clicking on the window
    if (input->isMousePressed(MouseButtonLeft) && !m_playMode)
    {
        m_playMode = true;
        input->enablePlayMode(m_playMode);
    }

    // Disable play mode when pressing the Escape key
    if (input->isKeyPressed(Key::KeyEscape) && m_playMode)
    {
        m_playMode = false;
        input->enablePlayMode(m_playMode);
    }
    
    // Toggle point lights on/off
    if (input->isKeyPressed(Key::Key1))
    {
        bool currentLightStatus = lighting->getPointLightsStatus();
        lighting->setPointLightsStatus(!currentLightStatus);
    }
    
    // Toggle directional light on/off
    if (input->isKeyPressed(Key::Key2))
    {
        bool currentLightStatus = lighting->getDirectionalLightStatus();
        lighting->setDirectionalLightStatus(!currentLightStatus);
    }

    // Toggle spotlight on/off
    if (input->isKeyPressed(Key::Key3))
    {
        bool currentLightStatus = lighting->getSpotlightStatus();
        lighting->setSpotlightStatus(!currentLightStatus);
    }
    
    // Toggle wireframe mode on/off
    if (input->isKeyPressed(Key::Key4))
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
    glm::vec2 cursorPosition = input->getMousePosition();

    // Toggle to print the cords of the cursor
    if (input->isKeyPressed(Key::Key3))
    {
        std::cout << "Mouse Coordinates: (" << cursorPosition.x << ", " << cursorPosition.y << ")" << std::endl;
    }

    // check all buttons to see if interaction have been made by the user with the mouse
    for (auto & button : m_buttonRefs)
    {
        float buttonRightX = (button->getPosition().x / 2) + std::abs(button->getScale().x / 4);
        float buttonLeftX = (button->getPosition().x / 2) - std::abs(button->getScale().x / 4);
        float buttonBottomY = (-button->getPosition().y / 2) + std::abs(button->getScale().y / 4);
        float buttonTopY = (-button->getPosition().y / 2) - std::abs(button->getScale().y / 4);
        // when mouse is inside the button
        if (cursorPosition.x <= buttonRightX && cursorPosition.x >= buttonLeftX && 
            cursorPosition.y <= buttonBottomY && cursorPosition.y >= buttonTopY)
        {  
                // Change button texture when hovering
                if (!m_buttonTextureSwitched)
                {
                    button->setTexture(m_buttonHoveringTexture);
                    m_buttonTextureSwitched = true;
                }


                // Toggle texture when you press the button
                if (input->isMousePressed(MouseButtonLeft))
                {
                    m_instancedTextureSwitched = !m_instancedTextureSwitched;
                    if (m_instancedTextureSwitched)
                    {
                        m_instancedEntity->setTexture(m_instancedEntityTexture2Ptr);
                    }
                    else
                    {
                        m_instancedEntity->setTexture(m_instancedEntityTexture1Ptr);
                    }
                }
                else
                {
                    // Reset button texture to hovering after mouse click
                    button->setTexture(m_buttonHoveringTexture);
                }

                //while the mouse is held down keep the texture of the button in the down position
                if (input->isMouseDown(MouseButtonLeft)) button->setTexture(m_buttonDownTexture);
        }
        else if(m_buttonTextureSwitched)
        {
            // Reset the texture to up position when mouse leaves the button
            button->setTexture(m_buttonUpTexture);
            m_buttonTextureSwitched = false;
        }
    }
    
    // Adjust camera speed if Shift key is pressed
    if (input->isKeyDown(Key::KeyShift)) {
        m_movementSpeed = m_originalMovementSpeed * 2.0f;
    }
    else {
        m_movementSpeed = m_originalMovementSpeed;
    }

    // Update the camera's position
    m_cam->setPosition(m_position + m_playerHeightOffset);


    float sensitivity = 0.1f;  // Sensitivity factor for mouse movement
    m_yaw += input->getMouseXAxis() * sensitivity;
    m_pitch -= input->getMouseYAxis() * sensitivity;

    // Clamp the pitch value to prevent flipping the camera
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    // Update the camera's forward direction based on yaw and pitch
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cam->setForwardDirection(glm::normalize(direction));

    // Handle input for player movement based on camera direction
    glm::vec3 forward = m_cam->getForwardDirection();
    glm::vec3 up = m_cam->getUpwardDirection();
    glm::vec3 right = glm::normalize(glm::cross(forward, up));

    m_rotation.y = glm::radians(-m_yaw);

    // Project forward vector onto the XZ plane to remove vertical component
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    
    if (input->isKeyDown(Key::KeyW))
        m_position += forward * m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyS))
        m_position -= forward * m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyA))
        m_position -= right * m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyD))
        m_position += right * m_movementSpeed * deltaTime;

    // Handle input for player rotation
    if (input->isKeyDown(Key::KeyQ))
        m_position.y -= m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyE))
        m_position.y += m_movementSpeed * deltaTime;

    glm::vec2 mouseScroll = input->getMouseScroll();
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

void MyPlayer::addButtonRef(QuadEntity* buttonRef)
{
    m_buttonRefs.push_back(buttonRef);
}

void MyPlayer::setButtonTextures(TexturePtr buttonUpTexture, TexturePtr buttonHoveringTexture, TexturePtr buttonDownTexture)
{
    m_buttonUpTexture = buttonUpTexture;
    m_buttonHoveringTexture = buttonHoveringTexture;
    m_buttonDownTexture = buttonDownTexture;
}

void MyPlayer::setInstancedEntity(InstancedMeshEntity* instancedEntityRef, TexturePtr texture1, TexturePtr texture2)
{
    m_instancedEntity = instancedEntityRef;
    m_instancedEntityTexture1Ptr = texture1;
    m_instancedEntityTexture2Ptr = texture2;
}