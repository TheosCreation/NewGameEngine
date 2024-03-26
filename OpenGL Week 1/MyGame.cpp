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
		hexagon->setTexture(lava);

		m_hexagon1 = hexagon;
	}

	//creates a second hexagon
	{
		auto hexagon = getEntitySystem()->createEntity<HexagonEntity>();

		hexagon->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		hexagon->setPosition(glm::vec3(-2.0f, 0.0f, 0.0f) * m_entitySystem->globalScale);
		hexagon->setRotation(glm::vec3(0, 0, 0));
		hexagon->setTexture(lava);

		m_hexagon2 = hexagon;
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	auto m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0, 0, 0) * m_entitySystem->globalScale);
	m_player->setPosition(glm::vec3(0, 0, 3.0f) * m_entitySystem->globalScale);

	//enabling play mode
	//getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(float deltaTime)
{
	m_roty += 0.1f * deltaTime;

	m_hexagon1->setRotation(glm::vec3(m_hexagon1->getRotation().x, m_roty, m_hexagon1->getRotation().z));
	m_hexagon2->setRotation(glm::vec3(m_hexagon2->getRotation().x, m_roty, m_hexagon2->getRotation().z));
}
