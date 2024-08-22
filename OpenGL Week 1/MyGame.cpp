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
	auto& resourceManager = ResourceManager::GetInstance();
	auto& lightManager = LightManager::GetInstance();
	//Loading texture resources
	
	// create a cube map texture and set the texture of the skybox to the cubemap texture
	std::vector<std::string> skyboxCubeMapTextureFilePaths;
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Right.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Left.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Top.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Bottom.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Back.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Front.png");
	TextureCubeMapPtr skyBoxTexture = resourceManager.createCubeMapTextureFromFile(skyboxCubeMapTextureFilePaths);
	Texture2DPtr sciFiSpace = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
	Texture2DPtr shipReflectiveMap = resourceManager.createTexture2DFromFile("Resources/Textures/ReflectionMap_White.png");
	HeightMapPtr heightmap = resourceManager.createHeightMapFromFile("Resources/Textures/Heightmap0.jpg");
	MeshPtr fighterShip = resourceManager.createMeshFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj");
	InstancedMeshPtr mineMesh = resourceManager.createInstancedMeshFromFile("Resources/Meshes/Space/SM_Prop_Mine_01.obj");

	auto& graphicsEngine = GraphicsEngine::GetInstance();
	//Loading Shaders into the graphics engine
	ShaderPtr quadShader = graphicsEngine.createShader({
			L"QuadShader",
			L"QuadShader"
		});
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
	m_terrain = getEntitySystem()->createEntity<TerrainEntity>();
	m_terrain->setHeightmapTexture(heightmap);
	m_terrain->generateTerrainMesh();
	m_terrain->setScale(glm::vec3(0.5f));
	m_terrain->setPosition(glm::vec3(0, 0, 0));
	m_terrain->setTexture(sciFiSpace);
	//m_terrain->setColor(Color::Red);
	m_terrain->setShader(meshShader);

	//set the skybox texture
	m_skyBox->setTexture(skyBoxTexture);

	//Creating statue obj
	m_ship = getEntitySystem()->createEntity<MeshEntity>();
	m_ship->setScale(glm::vec3(0.05f));
	m_ship->setPosition(glm::vec3(0, 0, 0));
	m_ship->setShininess(32.0f);
	m_ship->setTexture(sciFiSpace);
	m_ship->setReflectiveMapTexture(shipReflectiveMap);
	m_ship->setMesh(fighterShip);
	m_ship->setShader(meshShader);
	
	//Creating instanced tree obj
	m_instanceMines = getEntitySystem()->createEntity<InstancedMeshEntity>();
	m_instanceMines->setShininess(32.0f);
	m_instanceMines->setTexture(sciFiSpace);
	m_instanceMines->setShader(instancedMeshShader);
	m_instanceMines->setMesh(mineMesh);


	//adds instances to the instanced mine mesh
	float spacing = 50.0f;
	for (int row = -4; row < 4; ++row) {
		for (int col = -4; col < 4; ++col) {
			for (int seg = -4; seg < 4; ++seg) {

				// Calculate the position of the current tree based on the grid and spacing
				glm::vec3 position = glm::vec3(col * spacing, seg * spacing, row * spacing);

				if (position == glm::vec3(0.0f)) break;

				// Generate random rotation angles
				float angleX = randomNumber(360.0f);
				float angleY = randomNumber(360.0f);
				float angleZ = randomNumber(360.0f);

				float randomScale = randomNumber(0.15f);

				// Add the tree instance with random rotations
				mineMesh->addInstance(position, glm::vec3(0.05f + randomScale), glm::vec3(angleX, angleY, angleZ));
			}
		}
	}
	
	//Init instance buffer
	mineMesh->initInstanceBuffer();
	
	//Creating the player object
	//all the input managements, creation of camera are inside Player class
	m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setScale(glm::vec3(0.0f));
	m_player->setPosition(glm::vec3(0.0f, 20.0f, 0.0f));

	// Initialize point lights 
	{
		auto pointLightObject = getEntitySystem()->createEntity<MeshEntity>();
		pointLightObject->setPosition(glm::vec3(25.0f, 15.0f, 0.0f));
		pointLightObject->setColor(Color::Blue);
		pointLightObject->setMesh(m_sphereMesh);
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
		auto pointLightObject = getEntitySystem()->createEntity<MeshEntity>();
		pointLightObject->setPosition(glm::vec3(-25.0f, 15.0f, 0.0f));
		pointLightObject->setColor(Color::Red);
		pointLightObject->setMesh(m_sphereMesh);
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
	directionalLight.Direction = glm::vec3(0.5f, -1.0f, -0.5f);
	directionalLight.Color = glm::vec3(0.1f, 0.1f, 0.1f);
	directionalLight.SpecularStrength = 0.5f;
	lightManager.createDirectionalLight(directionalLight);

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
	lightManager.createSpotLight(spotLight);
}

void MyGame::onUpdate(float deltaTime)
{
}

void MyGame::onFixedUpdate()
{
}

void MyGame::onLateUpdate(float deltaTime)
{
}