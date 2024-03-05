#include "MyPlayer.h"

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
	m_cam->setPosition(glm::vec3(0, 0, 0));
}

void MyPlayer::onUpdate(float deltaTime)
{
	auto input = getGame()->getInputManager();

	//rotating the camera thorugh mouse movements
	m_camRotY += input->getMouseXAxis() * 0.01f;
	m_camRotX += input->getMouseYAxis() * 0.01f;

	if (m_camRotX > 1.57f)
		m_camRotX = 1.57f;
	else if (m_camRotX < -1.57f)
		m_camRotX = -1.57f;

	m_cam->setRotation(glm::vec3(m_camRotX, m_camRotY, 0));


	//moving the camera along x and z axis through keyboard input events (W,A,S,D)
	glm::mat4 worldMatCam;
	m_cam->getWorldMatrix(worldMatCam);


	glm::vec3 forwardDir = getForwardDirection(worldMatCam);
	glm::vec3 rightwardDir = getRightwardDirection(worldMatCam);


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

	// Combine the forward and rightward directions
	glm::vec3 moveDirection = (forwardDir * moveForward + rightwardDir * moveRightward);

	glm::vec3 pos = m_cam->getPosition() + moveDirection * speed * deltaTime;

	m_cam->setPosition(pos);
}
