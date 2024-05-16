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
	
	auto quadShader = m_graphicsEngine->createShader({
			L"QuadShader",
			L"QuadShader"
		});
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

	//ui button
	{
		auto entity = getEntitySystem()->createEntity<QuadEntity>();
		entity->setScale(glm::vec3(0.15f, 0.15f, 0.15f));
		entity->setPosition(glm::vec3(0.0f, 100.0f, 1.0f));
		entity->setTexture(statueTexture);
		entity->setShader(quadShader);
	}
	
	//creating statue
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(0.15f, 0.15f, 0.15f));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(statueTexture);
		entity->setMesh(statueMesh);
		entity->setShader(meshShader);
		m_statue = entity;
	}
	
	//creating instanced tree
	{
		auto entity = getEntitySystem()->createEntity<InstancedMeshEntity>();
		entity->setTexture(statueTexture);
		entity->setShader(instancedMeshShader);

		entity->setMesh(instancedTreeMesh);
		float spacing = 20.0f;
		for (int row = -16; row < 16; ++row) {
			for (int col = -16; col < 16; ++col) {
				if (row == 0 && col == 0) break;

				// Calculate the position of the current tree based on the grid and spacing
				glm::vec3 position = glm::vec3(col * spacing, 0.0f, row * spacing);

				// Generate random rotation angles
				float angleX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
				float angleY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 360.0f;
				float angleZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;

				// Add the tree instance with random rotations
				instancedTreeMesh->addInstance(position, glm::vec3(0.1f, 0.05f, 0.1f), glm::vec3(angleX, angleY, angleZ));
			}
		}

		// Init instance buffer
		instancedTreeMesh->initInstanceBuffer();

		m_instancedTree = entity;
	}
	
	//creating skybox
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(800, 800, 800));
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

}

void MyGame::onUpdate(float deltaTime)
{
	m_rotz += glm::radians(40.0f * deltaTime);
	m_roty += glm::radians(5.0f * deltaTime);

	m_skybox->setRotation(glm::vec3(0, m_roty, 0));

	m_statue->setPosition(m_player->getPosition());
	m_statue->setRotation(m_player->getRotation());
}