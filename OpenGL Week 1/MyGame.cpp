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
	//auto wood = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/wood.jpg"));

	auto cobblestone = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/cobblestone.png"));
	auto lava = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/lava.jpg"));

	srand((unsigned int)time(NULL));

	auto pyramid = getEntitySystem()->createEntity<PyramidEntity>();

	pyramid->setScale(glm::vec3(5, 5, 5));
	pyramid->setPosition(glm::vec3(0.0f, (5 / 2.0f) + 3.5f, 0.0f));
	pyramid->setRotation(glm::vec3(0, 0, 0));
	pyramid->setTexture(cobblestone);

	for (auto y = -4; y < 4; y++)
	{
		for (auto x = -4; x < 4; x++)
		{

			auto cube = getEntitySystem()->createEntity<CubeEntity>();

			auto roty = (rand() % 600) + (200.0f);
			roty /= 1000.0f;
			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			auto height = width;


			cube->setScale(glm::vec3(width, height, width));
			cube->setPosition(glm::vec3(x * 1.4f, (height / 2.0f) - 3.5f, y * 1.4f));
			cube->setRotation(glm::vec3(0, roty, 0));
			cube->setTexture(cobblestone);
		}
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	auto m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setPosition(glm::vec3(0, 0, 0));

	//enabling play mode
	getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(float deltaTime)
{
	
}
