#include "MyGame.h"
#include "MyPlayer.h"
#include <time.h>

MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::onCreate()
{
	Game::onCreate();

	//loading texture resource
	auto wood = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/wood.jpg"));
	auto wall = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/wall.jpg"));
	
	auto cube = getEntitySystem()->createEntity<CubeEntity>();
	cube->setScale(Vec3(2.0f, 0.1f, 2.0f));
	cube->setPosition(Vec3(0, -1, 0));
	cube->setTexture(wall);

	srand((unsigned int)time(NULL));

	for (auto y = -1; y < 1; y++)
	{
		for (auto x = -1; x < 1; x++)
		{
			auto cube = getEntitySystem()->createEntity<CubeEntity>();
			auto height = (rand() % 120) + (80.0f);
			height /= 100.0f;

			auto roty = (rand() % 600) + (200.0f);
			roty /= 1000.0f;
			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;


			cube->setScale(Vec3(width, height, width));
			cube->setPosition(Vec3(x * 1.4f, (height / 2.0f) - 3.5f, y * 1.4f));
			cube->setRotation(Vec3(0, roty, 0));
			cube->setTexture(wood);
		}
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	auto m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setPosition(Vec3(0, 0, 0));

	//enabling play mode
	/* Remove after DEBUG
	getInputManager()->enablePlayMode(true);
	*/
}

void MyGame::onUpdate(float deltaTime)
{
	
}
