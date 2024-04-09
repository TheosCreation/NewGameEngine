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
	m_entity = getEntitySystem()->createEntity<Entity>();
	m_cam = getEntitySystem()->createEntity<Camera>();
}

void MyPlayer::onUpdate(float deltaTime)
{
    auto input = getGame()->getInputManager();



    //starts automatic input when inactive
    const float orbitResetTime = 1.0f; // Time in seconds after which orbit resets
    if (!input->isKeyDown(Key::KeyA) && !input->isKeyDown(Key::KeyD) &&
        !input->isKeyDown(Key::KeyW) && !input->isKeyDown(Key::KeyS)) {
        m_inactivityTimer += deltaTime;
        if (m_inactivityTimer >= orbitResetTime) {
            //orbits slowly
            m_orbitHorizontal += m_orbitSpeed * deltaTime;
        }
    }
    else {
        // Reset timer if any input detected
        m_inactivityTimer = 0.0f;
    }

    if (input->isKeyDown(Key::KeyA))
        m_orbitHorizontal -= m_orbitSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyD))
        m_orbitHorizontal += m_orbitSpeed * deltaTime;

    if (input->isKeyDown(Key::KeyW))
        m_orbitRadius -= m_zoomSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyS))
        m_orbitRadius += m_zoomSpeed * deltaTime;

    m_orbitRadius = std::max(m_minimumOrbitalRadius, std::min(m_orbitRadius, m_maximumOrbitalRadius));

    m_position.x = m_orbitRadius * sin(m_orbitHorizontal);
    m_position.z = m_orbitRadius * cos(m_orbitHorizontal);

    // Update the camera's position
    m_cam->setPosition(m_position);
}