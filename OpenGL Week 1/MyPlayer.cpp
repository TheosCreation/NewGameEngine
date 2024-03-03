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
	m_cam->setPosition(Vec3(0, 0, 0));
}

void MyPlayer::onUpdate(float deltaTime)
{
	auto input = m_game->getInputManager();
	m_elapsedSeconds += deltaTime;

	if (m_entity && m_elapsedSeconds >= 3.0f)
	{
		m_entity->release();
		m_entity = nullptr;
	}

	//rotating the camera thorugh mouse movements
	m_camRotY += input->getMouseXAxis() * 0.01f;
	m_camRotX += input->getMouseYAxis() * 0.01f;

	if (m_camRotX > 1.57f)
		m_camRotX = 1.57f;
	else if (m_camRotX < -1.57f)
		m_camRotX = -1.57f;

	m_cam->setRotation(Vec3(m_camRotX, m_camRotY, 0));


	//moving the camera along x and z axis through keyboard input events (W,A,S,D)
	Mat4 worldMatCam;
	m_cam->getWorldMatrix(worldMatCam);


	auto forwardDir = worldMatCam.getForwardDirection();
	auto rightwardDir = worldMatCam.getRightwardDirection();


	auto speed = 2.0f;
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

	//compute position by moving along the forward axis and rightward axis
	//forward axis and rightward axis are provided by the world matrix of the camera

	auto pos = m_cam->getPosition() + (forwardDir * moveForward) * speed * deltaTime;
	pos = pos + (rightwardDir * moveRightward) * speed * deltaTime;

	m_cam->setPosition(pos);
}
