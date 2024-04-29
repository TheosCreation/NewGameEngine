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

	auto skyTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Sky.png"));

	//loading sphere mesh resource
	auto sphereMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/sphere.obj"));


	auto ninjaAttackSpriteSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Ninja_Attack.png"));


	auto hexagonShader = getGraphicsEngine()->createShader({
		L"HexagonShader",
		L"HexagonShader"
		});
	
	auto quadShader = getGraphicsEngine()->createShader({
		L"QuadShader",
		L"QuadShader"
		});

	auto animatedQuadShader = getGraphicsEngine()->createShader({
		L"AnimatedQuadShader",
		L"AnimatedQuadShader"
		});
	
	auto skyboxShader = m_graphicsEngine->createShader({
			L"SkyBoxShader",
			L"SkyBoxShader"
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

	//creating skybox
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(1000, 1000, 1000));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(skyTexture);
		entity->setMesh(sphereMesh);
		entity->setShader(skyboxShader);
		m_skybox = entity;
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
	m_rotz += glm::radians(40.0f * deltaTime);

	m_hexagon1->setRotation(glm::vec3(m_hexagon1->getRotation().x, m_hexagon1->getRotation().y, -m_rotz));
	m_hexagon2->setRotation(glm::vec3(m_hexagon2->getRotation().x, m_hexagon2->getRotation().y, m_rotz));
}