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
	//auto alien = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Alien.png"));
	//alien->getTexture2D()->setMirrored();

	auto skyTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Sky.jpg"));

	//loading sphere mesh resource
	auto sphereMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/sphere.obj"));

	auto statueTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/PolygonAncientWorlds_Texture_01_A.png"));
	auto statueMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/SM_Prop_Statue_01.obj"));


	//auto ninjaAttackSpriteSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Ninja_Attack.png"));


	//auto hexagonShader = getGraphicsEngine()->createShader({
	//	L"HexagonShader",
	//	L"HexagonShader"
	//	});
	
	auto skyboxShader = m_graphicsEngine->createShader({
			L"SkyBoxShader",
			L"SkyBoxShader"
		});

	//creating statue
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(0.05, 0.05, 0.05));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(statueTexture);
		entity->setMesh(statueMesh);
		entity->setShader(skyboxShader);
		m_statue = entity;
	}
	
	//creating skybox
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(100, 100, 100));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(skyTexture);
		entity->setMesh(sphereMesh);
		entity->setShader(skyboxShader);
		m_skybox = entity;
	}

	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0, 0, 0) * m_entitySystem->globalScale);
	m_player->setPosition(glm::vec3(0, 0.0f, 0.0f) * m_entitySystem->globalScale);

	//enabling play mode
	//getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(float deltaTime)
{
	m_rotz += glm::radians(40.0f * deltaTime);
	m_roty += glm::radians(5.0f * deltaTime);

	m_skybox->setRotation(glm::vec3(0, m_roty, 0));

	m_statue->setPosition(m_player->getPosition());
}