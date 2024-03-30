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
	auto alien = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Alien.png"));
	alien->getTexture2D()->setMirrored();

	auto ninjaAttackSpriteSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Ninja_Attack.png"));

	auto hexagonShader = getGraphicsEngine()->createShaderProgram({
		L"HexagonShader",
		L"HexagonShader"
		});
	
	auto quadShader = getGraphicsEngine()->createShaderProgram({
		L"QuadShader",
		L"QuadShader"
		});

	auto animatedQuadShader = getGraphicsEngine()->createShaderProgram({
		L"AnimatedQuadShader",
		L"AnimatedQuadShader"
		});

	{
		//creates a the first hexagon
		m_hexagon1 = getEntitySystem()->createEntity<HexagonEntity>();

		m_hexagon1->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		m_hexagon1->setPosition(glm::vec3(3.0f, 4.0f, 0.0f) * m_entitySystem->globalScale);
		m_hexagon1->setRotation(glm::vec3(0, 0, 0));
		m_hexagon1->setShader(hexagonShader);
	}

	{
		//creates a second hexagon
		m_hexagon2 = getEntitySystem()->createEntity<HexagonEntity>();

		m_hexagon2->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		m_hexagon2->setPosition(glm::vec3(-3.0f, 4.0f, 0.0f) * m_entitySystem->globalScale);
		m_hexagon2->setRotation(glm::vec3(0, 0, 0));
		m_hexagon2->setShader(hexagonShader);
	}
	{

		//creates a first quad
		m_quad1 = getEntitySystem()->createEntity<QuadEntity>();

		m_quad1->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		m_quad1->setPosition(glm::vec3(3.0f, -4.0f, 0.0f) * m_entitySystem->globalScale);
		m_quad1->setRotation(glm::vec3(0, 0, 0));
		m_quad1->setShader(quadShader);
		m_quad1->setTexture(alien);
	}
	
	//creates a second quad
	{

		m_quad2 = getEntitySystem()->createEntity<AnimatedQuadEntity>();

		m_quad2->setScale(glm::vec3(4, 4, 4) * m_entitySystem->globalScale);
		m_quad2->setPosition(glm::vec3(-3.0f, -4.0f, 0.0f) * m_entitySystem->globalScale);
		m_quad2->setRotation(glm::vec3(0, 0, 0));
		m_quad2->setShader(animatedQuadShader);
		m_quad2->setTexture(ninjaAttackSpriteSheet);
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	auto m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0, 0, 0) * m_entitySystem->globalScale);
	m_player->setPosition(glm::vec3(0, 0, 5.0f) * m_entitySystem->globalScale);

	//enabling play mode
	//getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(float deltaTime)
{
	m_roty += glm::radians(40.0f * deltaTime);

	m_hexagon1->setRotation(glm::vec3(m_hexagon1->getRotation().x, -m_roty, m_hexagon1->getRotation().z));
	m_hexagon2->setRotation(glm::vec3(m_hexagon2->getRotation().x, m_roty, m_hexagon2->getRotation().z));
}
