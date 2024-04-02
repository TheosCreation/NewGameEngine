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
    float speed = 50.0f;

    float moveOffset = speed * deltaTime;

    // Alternate between moving left and right
    static bool moveLeft = true;
    if (moveLeft) {
        m_position.x -= moveOffset;
    }
    else {
        m_position.x += moveOffset;
    }

    // if the camera reaches the boundary it switch to the other direction
    const float leftBoundary = -150.0f;
    const float rightBoundary = 150.0f;
    if (m_position.x <= leftBoundary || m_position.x >= rightBoundary) {
        moveLeft = !moveLeft;
    }

    m_cam->setPosition(m_position);
}
