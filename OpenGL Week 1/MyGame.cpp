/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : MyGame.cpp
Description : MyGame class is a stripped down class of the base game class to be able for end user to create their own entities
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

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
	
	//Loading texture resources
	TexturePtr buttonDownTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/Button_Down.png"));
	TexturePtr buttonHoveringTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/Button_Hovering.png"));
	TexturePtr buttonUpTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/Button_Up.png"));

	TexturePtr groundTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/dirt.jpg"));

	TexturePtr skyTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/SkyBox.jpg"));

	TexturePtr colouredAncientTextureSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/PolygonAncientWorlds_Texture_01_A.png"));
	TexturePtr plainAncientTextureSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/PolygonAncientWorlds_Statue_01.png"));

	//Loading meshes
	MeshPtr sphereMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/sphere.obj"));
	MeshPtr statueMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/SM_Prop_Statue_01.obj"));
	InstancedMeshPtr instancedTreeMesh = std::dynamic_pointer_cast<InstancedMesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/SM_Env_Tree_Palm_01.obj", true));
	
	//Loading Shader
	ShaderPtr quadShader = m_graphicsEngine->createShader({
			L"QuadShader",
			L"QuadShader"
		});
	ShaderPtr meshShader = m_graphicsEngine->createShader({
			L"MeshShader",
			L"MeshShader"
		});
	ShaderPtr skyboxShader = m_graphicsEngine->createShader({
			L"SkyBoxShader",
			L"SkyBoxShader"
		});
	ShaderPtr instancedMeshShader = m_graphicsEngine->createShader({
			L"InstancedMesh",
			L"InstancedMesh"
		});

	//Creating statue obj
	m_statue = getEntitySystem()->createEntity<MeshEntity>();
	m_statue->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	m_statue->setPosition(glm::vec3(0, 0, 0));
	m_statue->setShininess(32.0f);
	m_statue->setTexture(colouredAncientTextureSheet);
	m_statue->setMesh(statueMesh);
	m_statue->setShader(meshShader);
	
	//Creating instanced tree obj
	m_instancedTree = getEntitySystem()->createEntity<InstancedMeshEntity>();
	m_instancedTree->setTexture(colouredAncientTextureSheet);
	m_instancedTree->setShader(instancedMeshShader);

	m_instancedTree->setMesh(instancedTreeMesh);
	float spacing = 30.0f;
	for (int row = -16; row < 16; ++row) {
		for (int col = -16; col < 16; ++col) {
			if (row == 0 && col == 0) break;

			// Calculate the position of the current tree based on the grid and spacing
			glm::vec3 position = glm::vec3(col * spacing, 0.0f, row * spacing);

			// Generate random rotation angles
			float angleX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;
			float angleY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 360.0f;
			float angleZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0f - 5.0f;

			float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.05f;

			// Add the tree instance with random rotations
			instancedTreeMesh->addInstance(position, glm::vec3(0.05f, 0.025f, 0.05f) + randomScale, glm::vec3(angleX, angleY, angleZ));
		}
	}

	//Init instance buffer
	instancedTreeMesh->initInstanceBuffer();

	//Creating ground object
	m_ground = getEntitySystem()->createEntity<MeshEntity>();
	m_ground->setScale(glm::vec3(800, 1, 800));
	m_ground->setPosition(glm::vec3(0, -1, 0));
	m_ground->setTexture(groundTexture);
	m_ground->setMesh(sphereMesh);
	m_ground->setShader(meshShader);
	
	//Creating skybox object
	m_skybox = getEntitySystem()->createEntity<MeshEntity>();
	m_skybox->setScale(glm::vec3(1000.0f));
	m_skybox->setPosition(glm::vec3(0, 0, 0));
	m_skybox->setTexture(skyTexture);
	m_skybox->setMesh(sphereMesh);
	m_skybox->setShader(skyboxShader);

	//Creating the player object
	//all the input managements, creation of camera are inside Player class
	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0.0f));
	m_player->setPosition(glm::vec3(0.0f));

	//ui button
	m_button = getEntitySystem()->createEntity<QuadEntity>();
	m_button->setScale(glm::vec3(400.0f * -1, 200.0f, 1.0f));
	m_button->setPosition(glm::vec3(200.0f * m_uiScaleX, 100.0f * m_uiScaleY, 0.0f));
	m_button->setTexture(buttonUpTexture);
	m_button->setShader(quadShader);
	m_player->addButtonRef(m_button);
	m_player->setInstancedEntity(m_instancedTree, colouredAncientTextureSheet, plainAncientTextureSheet);
	m_player->setButtonTextures(buttonUpTexture, buttonHoveringTexture, buttonDownTexture);
}

void MyGame::onUpdate(float deltaTime)
{
	//Slowly rotate the skybox
	m_rotz += glm::radians(40.0f * deltaTime);
	m_skybox->setRotation(glm::vec3(0, m_roty, 0));

	m_statue->setPosition(m_player->getPosition());
	m_statue->setRotation(m_player->getRotation());
}