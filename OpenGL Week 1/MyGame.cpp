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
	auto cobblestone = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/cobblestone.png"));
	auto lava = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/lava.jpg"));

	srand((unsigned int)time(NULL));

	//creates a the first hexagon
	{
		auto hexagon = getEntitySystem()->createEntity<HexagonEntity>();

		hexagon->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		hexagon->setPosition(glm::vec3(2.0f, 0.0f, 0.0f) * m_entitySystem->globalScale);
		hexagon->setRotation(glm::vec3(0, 0, 0));
	}

	//creates a second hexagon
	{
		auto hexagon = getEntitySystem()->createEntity<HexagonEntity>();

		hexagon->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		hexagon->setPosition(glm::vec3(-2.0f, 0.0f, 0.0f) * m_entitySystem->globalScale);
		hexagon->setRotation(glm::vec3(0, 0, 0));
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
