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

	m_camRotY += input->getMouseXAxis() * 0.01f;
	m_camRotX += input->getMouseYAxis() * 0.01f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_camRotY));
	direction.y = sin(glm::radians(m_camRotX));
	direction.z = sin(glm::radians(m_camRotY));

	//m_cam->setForwardDirection(glm::normalize(direction));


	float speed = 2.0f;
	float moveForward = 0, moveRightward = 0;

	if (input->isKeyDown(Key::KeyW))
	{
		moveForward = 1;
	}
	if (input->isKeyDown(Key::KeyS))
	{
		moveForward = -1;
	}
	if (input->isKeyDown(Key::KeyA))
	{
		moveRightward = -1;
	}
	if (input->isKeyDown(Key::KeyD))
	{
		moveRightward = 1;
	}
    m_cam->setPosition(m_position);
}
