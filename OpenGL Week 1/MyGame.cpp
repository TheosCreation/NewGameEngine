#include "MyGame.h"

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	Game::onCreate();
	
	m_player = getEntitySystem()->createEntity<MyPlayer>();
}

void MyGame::onUpdate(float deltaTime)
{
	
}
