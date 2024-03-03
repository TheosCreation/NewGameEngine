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
}
