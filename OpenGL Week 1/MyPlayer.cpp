#include "MyPlayer.h"
#include <algorithm>

MyPlayer::MyPlayer()
{
    setCameraPosition(glm::vec3(0, 5.0f, 5.0f));
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{
	m_entity = getEntitySystem()->createEntity<Entity>();
	m_cam = getEntitySystem()->createEntity<Camera>();
}

void MyPlayer::onUpdate(float deltaTime)
{
    auto input = getGame()->getInputManager();

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
        if (m_inactivityTimer >= orbitResetTime) {
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

    // Handle input for player movement
    if (input->isKeyDown(Key::KeyW))
        m_position.z += m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyS))
        m_position.z -= m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyA))
        m_position.x -= m_movementSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyD))
        m_position.x += m_movementSpeed * deltaTime;
}

void MyPlayer::setCameraPosition(glm::vec3 newPosition)
{
    m_camPosition = newPosition;
}