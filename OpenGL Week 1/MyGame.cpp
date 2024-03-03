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
	
	
	auto cube = getEntitySystem()->createEntity<CubeEntity>();
	cube->setScale(Vec3(6.8f, 0.1f, 6.8f));
	cube->setPosition(Vec3(0, -1, 0));

	srand((unsigned int)time(NULL));

	for (auto y = -2; y < 3; y++)
	{
		for (auto x = -2; x < 3; x++)
		{
			auto cube = getEntitySystem()->createEntity<CubeEntity>();
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;


			cube->setScale(Vec3(width, height, width));
			cube->setPosition(Vec3(x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f));
		}
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setPosition(Vec3(0, 0, 0));

	//enabling play mode
	getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(float deltaTime)
{
	
}
