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

    //need to add shift key to speed camera up
    if (input->isKeyDown(Key::KeyShift))
    {
        m_orbitSpeed = m_originalOrbitSpeed * 2.0f;
    }
    else
    {
        m_orbitSpeed = m_originalOrbitSpeed;
    }
    //starts automatic input when inactive
    const float orbitResetTime = 1.0f; // Time in seconds after which orbit resets
    if (!input->isKeyDown(Key::KeyLeft) && !input->isKeyDown(Key::KeyRight) &&
        !input->isKeyDown(Key::KeyUp) && !input->isKeyDown(Key::KeyDown)) {
        m_inactivityTimer += deltaTime;
        if (m_inactivityTimer >= orbitResetTime) {
            //orbits slowly
            m_orbitHorizontal += m_orbitSpeed * deltaTime;
        }
    }
    else {
        // reset timer if any input detected
        m_inactivityTimer = 0.0f;
    }

    if (input->isKeyDown(Key::KeyLeft))
        m_orbitHorizontal -= m_orbitSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyRight))
        m_orbitHorizontal += m_orbitSpeed * deltaTime;

    if (input->isKeyDown(Key::KeyUp))
        m_orbitRadius -= m_zoomSpeed * deltaTime;
    if (input->isKeyDown(Key::KeyDown))
        m_orbitRadius += m_zoomSpeed * deltaTime;

    m_orbitRadius = std::max(m_minimumOrbitalRadius, std::min(m_orbitRadius, m_maximumOrbitalRadius));

    m_position.x = m_orbitRadius * sin(m_orbitHorizontal);
    m_position.z = m_orbitRadius * cos(m_orbitHorizontal);

    // Update the camera's position
    m_cam->setPosition(m_position);
}