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
	auto buttonDownTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Button_Down.png"));
	auto buttonUpTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Button_Up.png"));

	auto skyTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/Sky.jpg"));

	//loading sphere mesh resource
	auto sphereMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/sphere.obj"));

	auto statueTexture1 = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/PolygonAncientWorlds_Texture_01_A.png"));
	auto statueTexture2 = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/PolygonAncientWorlds_Statue_01.png"));
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

	

	//creating statue
	m_statue = getEntitySystem()->createEntity<MeshEntity>();
	m_statue->setScale(glm::vec3(0.15f, 0.15f, 0.15f));
	m_statue->setPosition(glm::vec3(0, 0, 0));
	m_statue->setTexture(statueTexture1);
	m_statue->setMesh(statueMesh);
	m_statue->setShader(meshShader);
	
	//creating instanced tree
	auto m_instancedTree = getEntitySystem()->createEntity<InstancedMeshEntity>();
	m_instancedTree->setTexture(statueTexture1);
	m_instancedTree->setShader(instancedMeshShader);

	m_instancedTree->setMesh(instancedTreeMesh);
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

	//creating ground object
	m_ground = getEntitySystem()->createEntity<MeshEntity>();
	m_ground->setScale(glm::vec3(800, 1, 800));
	m_ground->setPosition(glm::vec3(0, -1, 0));
	m_ground->setTexture(buttonDownTexture);
	m_ground->setMesh(sphereMesh);
	m_ground->setShader(meshShader);
	
	//creating skybox object
	m_skybox = getEntitySystem()->createEntity<MeshEntity>();
	m_skybox->setScale(glm::vec3(800, 800, 800));
	m_skybox->setPosition(glm::vec3(0, 0, 0));
	m_skybox->setTexture(skyTexture);
	m_skybox->setMesh(sphereMesh);
	m_skybox->setShader(skyboxShader);

	//creating the player object
	//all the input managements, creation of camera are moved inside Player class
	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0, 0, 0) * m_entitySystem->globalScale);
	m_player->setPosition(glm::vec3(0, 0.0f, 0.0f) * m_entitySystem->globalScale);

	//ui button
	m_button = getEntitySystem()->createEntity<QuadEntity>();
	m_button->setScale(glm::vec3(200.0f, 100.0f, 1.0f));
	m_button->setPosition(glm::vec3(100.0f * m_uiScaleX, 100.0f * m_uiScaleY, 0.0f));
	m_button->setTexture(buttonUpTexture);
	m_button->setShader(quadShader);
	m_player->addButtonRef(m_button);
	m_player->setInstancedEntity(m_instancedTree, statueTexture1, statueTexture2);
}

void MyGame::onUpdate(float deltaTime)
{
	m_rotz += glm::radians(40.0f * deltaTime);
	m_roty += glm::radians(5.0f * deltaTime);

	m_skybox->setRotation(glm::vec3(0, m_roty, 0));

	m_statue->setPosition(m_player->getPosition());
	m_statue->setRotation(m_player->getRotation());
}