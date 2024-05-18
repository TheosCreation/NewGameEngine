#include "MyPlayer.h"
#include <algorithm>

MyPlayer::MyPlayer()
{
    setCameraPosition(glm::vec3(0, 100.0f, 20.0f));
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{
	m_cam = getEntitySystem()->createEntity<Camera>();
    m_uiCamera = getEntitySystem()->createEntity<Camera>();
    m_uiCamera->setCameraType(CameraType::Orthogonal);
    input = getGame()->getInputManager();
}

void MyPlayer::onUpdate(float deltaTime)
{
    // Toggle automatic rotation with the R key
    if (input->isKeyPressed(Key::KeyR))
    {
        m_autoRotate = !m_autoRotate;
    }

    // Toggle cursor
    if (input->isKeyPressed(Key::Key1))
    {
        m_playMode = !m_playMode;
        input->enablePlayMode(m_playMode);
    }
    
    // Toggle wireframe mode
    if (input->isKeyPressed(Key::Key2))
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
        m_orbitSpeed = m_originalOrbitSpeed * 2.0f;
    }
    else {
        m_orbitSpeed = m_originalOrbitSpeed;
    }

    // Start automatic input when inactive
    const float orbitResetTime = 1.0f; // Time in seconds after which orbit resets
    if (!input->isKeyDown(Key::KeyLeft) && !input->isKeyDown(Key::KeyRight) &&
        !input->isKeyDown(Key::KeyUp) && !input->isKeyDown(Key::KeyDown)) {
        m_inactivityTimer += deltaTime;
        if (m_inactivityTimer >= orbitResetTime && m_autoRotate) {
            // Orbits slowly
            m_orbitHorizontal += m_orbitSpeed * deltaTime;
        }
    }
    else {
        // Reset timer if any input detected
        m_inactivityTimer = 0.0f;
    }

    // Handle input for camera movement
    if (input->isKeyDown(Key::KeyLeft))
        m_orbitHorizontal -= m_orbitSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyRight))
        m_orbitHorizontal += m_orbitSpeed * deltaTime;

    if (input->isKeyDown(Key::KeyUp))
        m_orbitRadius -= m_zoomSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyDown))
        m_orbitRadius += m_zoomSpeed * deltaTime;

    // Ensure orbit radius stays within specified bounds
    m_orbitRadius = std::max(m_minimumOrbitalRadius, std::min(m_orbitRadius, m_maximumOrbitalRadius));

    // Calculate camera position based on orbit
    m_camPosition.x = m_orbitRadius * sin(m_orbitHorizontal);
    m_camPosition.z = m_orbitRadius * cos(m_orbitHorizontal);

    // Update the camera's position
    m_cam->setPosition(m_camPosition);

    // Handle input for player movement based on camera rotation
    glm::vec3 forward = glm::normalize(glm::vec3(sin(m_orbitHorizontal), 0, cos(m_orbitHorizontal)));
    glm::vec3 right = glm::normalize(glm::vec3(forward.z, 0, -forward.x));

    if (input->isKeyDown(Key::KeyW))
        m_position -= forward * m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyS))
        m_position += forward * m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyA))
        m_position -= right * m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyD))
        m_position += right * m_movementSpeed * deltaTime;

    // Handle input for player rotation
    if (input->isKeyDown(Key::KeyQ))
        m_position.y -= m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyE))
        m_position.y += m_movementSpeed * deltaTime;

    m_rotation.y = m_orbitHorizontal;
}

void MyPlayer::setCameraPosition(glm::vec3 newPosition)
{
    m_camPosition = newPosition;
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