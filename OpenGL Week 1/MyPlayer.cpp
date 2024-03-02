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
}

void MyPlayer::onUpdate(float deltaTime)
{
	m_elapsedSeconds += deltaTime;

	if (m_entity && m_elapsedSeconds >= 3.0f)
	{
		m_entity->release();
		m_entity = nullptr;
	}
}
