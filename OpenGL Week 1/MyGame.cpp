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

	TexturePtr solidRedTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/Red.png"));
	TexturePtr solidBlueTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/Blue.png"));

	TexturePtr colouredAncientTextureSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/PolygonAncientWorlds_Texture_01_A.png"));
	TexturePtr plainAncientTextureSheet = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/PolygonAncientWorlds_Statue_01.png"));
	
	TexturePtr sciFiSpace = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png"));
	TexturePtr shipReflectiveMap = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile("Resources/Textures/ReflectionMap_White.png"));

	std::vector<std::string> skyboxCubeMapTextureFilePaths;
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Right.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Left.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Top.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Bottom.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Back.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Front.png");
	m_skyBoxTexture = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(skyboxCubeMapTextureFilePaths));

	
	MeshPtr sphereMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/sphere.obj"));
	MeshPtr cubeMesh = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/cube.obj"));

	//Loading meshes
	MeshPtr fighterShip = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj"));
	InstancedMeshPtr mineMesh = std::dynamic_pointer_cast<InstancedMesh>(getResourceManager()->createResourceFromFile("Resources/Meshes/Space/SM_Prop_Mine_01.obj", true));
	
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
	ShaderPtr solidColorMeshShader = m_graphicsEngine->createShader({
			L"SolidColorMesh",
			L"SolidColorMesh"
		});

	//Creating statue obj
	m_ship = getEntitySystem()->createEntity<MeshEntity>();
	m_ship->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
	m_ship->setPosition(glm::vec3(0, 0, 0));
	m_ship->setShininess(32.0f);
	m_ship->setTexture(sciFiSpace);
	m_ship->setReflectiveMapTexture(shipReflectiveMap);
	m_ship->setMesh(fighterShip);
	m_ship->setShader(meshShader);
	
	//Creating instanced tree obj
	m_instancedTree = getEntitySystem()->createEntity<InstancedMeshEntity>();
	m_instancedTree->setShininess(32.0f);
	m_instancedTree->setTexture(colouredAncientTextureSheet);
	m_instancedTree->setShader(instancedMeshShader);
	m_instancedTree->setMesh(mineMesh);
	
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
			mineMesh->addInstance(position, glm::vec3(0.05f, 0.025f, 0.05f) + randomScale, glm::vec3(angleX, angleY, angleZ));
		}
	}
	
	//Init instance buffer
	mineMesh->initInstanceBuffer();
	
	//Creating skybox object
	m_skybox = getEntitySystem()->createEntity<SkyboxEntity>();
	m_skybox->setTexture(m_skyBoxTexture);
	m_skybox->setMesh(cubeMesh);
	m_skybox->setShader(skyboxShader);

	//ui button
	m_button = getEntitySystem()->createEntity<QuadEntity>();
	m_button->setScale(glm::vec3(400.0f * -1, 200.0f, 1.0f));
	m_button->setPosition(glm::vec3(200.0f * m_uiScaleX, 100.0f * m_uiScaleY, 0.0f));
	m_button->setTexture(buttonUpTexture);
	m_button->setShader(quadShader);

	//Creating the player object
	//all the input managements, creation of camera are inside Player class
	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0.0f));
	m_player->setPosition(glm::vec3(0.0f));
	m_player->addButtonRef(m_button);
	m_player->setInstancedEntity(m_instancedTree, colouredAncientTextureSheet, plainAncientTextureSheet);
	m_player->setButtonTextures(buttonUpTexture, buttonHoveringTexture, buttonDownTexture);

	//auto cubeEntity = getEntitySystem()->createEntity<MeshEntity>();
	//cubeEntity->setPosition(glm::vec3(0.0f, 30.0f, 0.0f));
	//cubeEntity->setScale(glm::vec3(0.01f));
	//cubeEntity->setColor(Color::Green);
	//cubeEntity->setMesh(cubeMesh);
	//cubeEntity->setShader(solidColorMeshShader);

	// Initialize point lights 
	{
		auto pointLightObject = getEntitySystem()->createEntity<MeshEntity>();
		pointLightObject->setPosition(glm::vec3(25.0f, 15.0f, 0.0f));
		pointLightObject->setColor(Color::Blue);
		pointLightObject->setMesh(sphereMesh);
		pointLightObject->setShader(solidColorMeshShader);

		PointLight pointLight;
		pointLight.Position = pointLightObject->getPosition();
		pointLight.Color = Color::Blue;
		pointLight.SpecularStrength = 1.0f;
		pointLight.AttenuationConstant = 1.0f;
		pointLight.AttenuationLinear = 0.045f;
		pointLight.AttenuationExponent = 0.0075f;
		m_lightManager->createPointLight(pointLight);
	}

	{
		auto pointLightObject = getEntitySystem()->createEntity<MeshEntity>();
		pointLightObject->setPosition(glm::vec3(-25.0f, 15.0f, 0.0f));
		pointLightObject->setColor(Color::Red);
		pointLightObject->setMesh(sphereMesh);
		pointLightObject->setShader(solidColorMeshShader);

		PointLight pointLight;
		pointLight.Position = pointLightObject->getPosition();
		pointLight.Color = Color::Red;
		pointLight.SpecularStrength = 1.0f;
		pointLight.AttenuationConstant = 1.0f;
		pointLight.AttenuationLinear = 0.045f;
		pointLight.AttenuationExponent = 0.0075f;
		m_lightManager->createPointLight(pointLight);
	}

	// Create and initialize DirectionalLight struct
	DirectionalLight directionalLight;
	directionalLight.Direction = glm::vec3(0.5f, -1.0f, -0.5f);
	directionalLight.Color = glm::vec3(0.1f, 0.1f, 0.1f);
	directionalLight.SpecularStrength = 0.5f;
	m_lightManager->createDirectionalLight(directionalLight);

	// Create and initialize SpotLight struct
	SpotLight spotLight;
	spotLight.Position = glm::vec3(0.0f);
	spotLight.Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	spotLight.Color = Color::White;
	spotLight.SpecularStrength = 1.0f;
	spotLight.CutOff = glm::cos(glm::radians(25.0f));
	spotLight.OuterCutOff = glm::cos(glm::radians(35.0f));
	spotLight.AttenuationConstant = 1.0f;
	spotLight.AttenuationLinear = 0.014f;
	spotLight.AttenuationExponent = 0.0007f;
	m_lightManager->createSpotLight(spotLight);

}

void MyGame::onUpdate(float deltaTime)
{
}

void MyGame::onLateUpdate(float deltaTime)
{
	//m_ship->setPosition(m_player->getPosition());
	//m_ship->setRotation(m_player->getRotation() + glm::vec3(0.0f, glm::degrees(90.0f), 0.0f));
}