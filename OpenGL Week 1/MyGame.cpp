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
	//alien->getTexture2D()->setMirrored();
	auto skyTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Sky.jpg"));

	//loading sphere mesh resource
	auto sphereMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/sphere.obj"));

	auto statueTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/PolygonAncientWorlds_Texture_01_A.png"));
	auto statueMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/SM_Prop_Statue_01.obj"));
	auto instancedTreeMesh = std::dynamic_pointer_cast<InstancedMesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/SM_Env_Tree_Palm_01.obj", true));
	
	auto meshShader = m_graphicsEngine->createShader({
			L"MeshShader",
			L"MeshShader"
		});
	auto skyboxShader = m_graphicsEngine->createShader({
			L"SkyBoxShader",
			L"SkyBoxShader"
		});
	auto instancedMeshShader = m_graphicsEngine->createShader({
			L"InstancedMesh",
			L"InstancedMesh"
		});

	//creating statue
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(0.1, 0.1, 0.1));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(statueTexture);
		entity->setMesh(statueMesh);
		entity->setShader(meshShader);
		m_statue = entity;
	}
	
	//creating instanced statue
	{
		auto entity = getEntitySystem()->createEntity<InstancedMeshEntity>();
		entity->setTexture(statueTexture);
		entity->setShader(instancedMeshShader);

		entity->setMesh(instancedTreeMesh);
		for (int row = -5; row < 5; ++row) {
			for (int col = -5; col < 5; ++col) {
				// Calculate the position of the current soldier based on the grid and spacing
				glm::vec3 position = glm::vec3(col * 5.0f, 0.0f, row * 5.0f);

				float angleY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 360.0f;

				// Add the soldier instance
				instancedTreeMesh->addInstance(position, glm::vec3(0.01f), glm::vec3(0.0f, angleY, 0.0f));
			}
		}

		// Update instance buffer
		instancedTreeMesh->updateInstanceBuffer();

		m_instancedTree = entity;
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