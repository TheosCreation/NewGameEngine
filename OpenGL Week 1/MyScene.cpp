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

#include "MyScene.h"
#include "MyPlayer.h"
#include <time.h>

MyScene::MyScene(Game* game) : Scene(game)
{
}

MyScene::~MyScene()
{
}

void MyScene::onCreate()
{
	Scene::onCreate();
	auto& resourceManager = ResourceManager::GetInstance();
	auto& lightManager = LightManager::GetInstance();
	auto& graphicsEngine = GraphicsEngine::GetInstance();
	//Loading texture resources
	
	Texture2DPtr sciFiSpace = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
	Texture2DPtr shipReflectiveMap = resourceManager.createTexture2DFromFile("Resources/Textures/ReflectionMap_White.png");
	MeshPtr fighterShip = resourceManager.createMeshFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj");
	InstancedMeshPtr mineMesh = resourceManager.createInstancedMeshFromFile("Resources/Meshes/Space/SM_Prop_Mine_01.obj");

	HeightMapInfo buildInfo = { "Resources/Heightmaps/Heightmap0.raw", 512, 512, 1.0f };
	HeightMapPtr heightmap = resourceManager.createHeightMap(buildInfo);

	//Loading Shaders into the graphics engine
	ShaderPtr meshShader = graphicsEngine.createShader({
			L"MeshShader",
			L"MeshShader"
		});
	ShaderPtr instancedMeshShader = graphicsEngine.createShader({
			L"InstancedMesh",
			L"InstancedMesh"
		});
	ShaderPtr solidColorMeshShader = graphicsEngine.createShader({
			L"SolidColorMesh",
			L"SolidColorMesh"
		});

	//auto& entitySystem = EntitySystem::GetInstance();

	//m_terrain = m_entitySystem->createEntity<TerrainEntity>();
	//m_terrain->generateTerrainMesh(heightmap);
	//m_terrain->setPosition(Vector3(0, 0, 0));
	//m_terrain->setTexture(sciFiSpace);
	//m_terrain->setColor(Color::Red);
	//m_terrain->setShader(meshShader);

	//m_ship = m_entitySystem->createEntity<MeshEntity>();
	//m_ship->setScale(Vector3(0.05f));
	//m_ship->setPosition(Vector3(0, 0, 0));
	//m_ship->setShininess(32.0f);
	//m_ship->setTexture(sciFiSpace);
	//m_ship->setReflectiveMapTexture(shipReflectiveMap);
	//m_ship->setMesh(fighterShip);
	//m_ship->setShader(meshShader);
	
	//Creating instanced tree obj
	m_instanceMines = m_entitySystem->createEntity<InstancedMeshEntity>();
	m_instanceMines->setShininess(32.0f);
	m_instanceMines->setTexture(sciFiSpace);
	m_instanceMines->setShader(instancedMeshShader);
	m_instanceMines->setMesh(mineMesh);
	m_instanceMines->setReflectiveMapTexture(shipReflectiveMap);


	//adds instances to the instanced mine mesh
	float spacing = 50.0f;
	for (int row = -4; row < 4; ++row) {
		for (int col = -4; col < 4; ++col) {
			for (int seg = -4; seg < 4; ++seg) {

				// Calculate the position of the current tree based on the grid and spacing
				Vector3 position = Vector3(col * spacing, seg * spacing, row * spacing);

				if (position == Vector3(0.0f)) break;

				// Generate random rotation angles
				float angleX = randomNumber(360.0f);
				float angleY = randomNumber(360.0f);
				float angleZ = randomNumber(360.0f);

				float randomScale = randomNumber(0.15f);

				// Add the tree instance with random rotations
				mineMesh->addInstance(position, Vector3(0.05f + randomScale), Vector3(angleX, angleY, angleZ));
			}
		}
	}
	
	//Init instance buffer
	mineMesh->initInstanceBuffer();

	//Creating the player object
	//all the input managements, creation of camera are inside Player class
	m_player = m_entitySystem->createEntity<MyPlayer>();
	m_player->setScale(Vector3(0.0f));
	m_player->setPosition(Vector3(0.0f, 20.0f, 0.0f));

	// Initialize point lights 
	{
		auto pointLightObject = m_entitySystem->createEntity<MeshEntity>();
		pointLightObject->setPosition(Vector3(25.0f, 15.0f, 0.0f));
		pointLightObject->setColor(Color::Blue);
		pointLightObject->setMesh(gameOwner->getSphereMesh());
		pointLightObject->setShader(solidColorMeshShader);

		PointLight pointLight;
		pointLight.Position = pointLightObject->getPosition();
		pointLight.Color = Color::Blue;
		pointLight.SpecularStrength = 1.0f;
		pointLight.AttenuationConstant = 1.0f;
		pointLight.AttenuationLinear = 0.045f;
		pointLight.AttenuationExponent = 0.0075f;
		lightManager.createPointLight(pointLight);
	}

	{
		auto pointLightObject = m_entitySystem->createEntity<MeshEntity>();
		pointLightObject->setPosition(Vector3(-25.0f, 15.0f, 0.0f));
		pointLightObject->setColor(Color::Red);
		pointLightObject->setMesh(gameOwner->getSphereMesh());
		pointLightObject->setShader(solidColorMeshShader);

		PointLight pointLight;
		pointLight.Position = pointLightObject->getPosition();
		pointLight.Color = Color::Red;
		pointLight.SpecularStrength = 1.0f;
		pointLight.AttenuationConstant = 1.0f;
		pointLight.AttenuationLinear = 0.045f;
		pointLight.AttenuationExponent = 0.0075f;
		lightManager.createPointLight(pointLight);
	}

	// Create and initialize DirectionalLight struct
	DirectionalLight directionalLight;
	directionalLight.Direction = Vector3(0.5f, -1.0f, -0.5f);
	directionalLight.Color = Vector3(0.1f, 0.1f, 0.1f);
	directionalLight.SpecularStrength = 0.5f;
	lightManager.createDirectionalLight(directionalLight);

	// Create and initialize SpotLight struct
	SpotLight spotLight;
	spotLight.Position = Vector3(0.0f);
	spotLight.Direction = Vector3(0.0f, 0.0f, -1.0f);
	spotLight.Color = Color::White;
	spotLight.SpecularStrength = 1.0f;
	spotLight.CutOff = glm::cos(glm::radians(25.0f));
	spotLight.OuterCutOff = glm::cos(glm::radians(35.0f));
	spotLight.AttenuationConstant = 1.0f;
	spotLight.AttenuationLinear = 0.014f;
	spotLight.AttenuationExponent = 0.0007f;
	lightManager.createSpotLight(spotLight);
}

void MyScene::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;
	
	// Convert the Euler angles to a quaternion
	Quaternion shipRotation = Quaternion(glm::radians(glm::vec3(0.0f, m_elapsedSeconds * 10.0f, 0.0f)));
	Quaternion minesRotation = Quaternion(glm::radians(glm::vec3(0.0f, m_elapsedSeconds * 10.0f, 0.0f)));

	// Set the rotations using quaternions
	//m_ship->setRotation(shipRotation);
	//m_instanceMines->setRotation(minesRotation);
}

void MyScene::onFixedUpdate(float _fixedDeltaTime)
{
	Scene::onFixedUpdate(_fixedDeltaTime);
}

void MyScene::onLateUpdate(float deltaTime)
{
	Scene::onLateUpdate(deltaTime);
}

void MyScene::onQuit()
{
	Scene::onQuit();
}
