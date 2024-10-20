/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene1.cpp
Description : 
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Scene2.h"
#include "MyPlayer.h"
#include "Game.h"

Scene2::Scene2(Game* game) : Scene(game)
{
}

Scene2::~Scene2()
{
}

void Scene2::onCreate()
{
	Scene::onCreate();
	gameOwner->SetFullScreenShader();

	auto& resourceManager = ResourceManager::GetInstance();
	auto& lightManager = LightManager::GetInstance();
	auto& graphicsEngine = GraphicsEngine::GetInstance();
	//Loading texture resources

	//Creating the player object
	//all the input managements, creation of camera are inside Player class
	m_player = m_entitySystem->createEntity<MyPlayer>();
	m_player->setScale(Vector3(0.0f));
	m_player->setPosition(Vector3(0.0f, 20.0f, 0.0f));

	Texture2DPtr heightMapTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Heightmap0.jpg");
	Texture2DPtr shipReflectiveMap = resourceManager.createTexture2DFromFile("Resources/Textures/ReflectionMap_White.png");
	Texture2DPtr sciFiSpaceTexture2D = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
	Texture2DPtr ancientWorldsTexture2D = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonAncientWorlds_Texture_01_A.png");
	Texture2DPtr grassTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/grass.png");
	Texture2DPtr dirtTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/dirt.png");
	Texture2DPtr stoneTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/stone.png");
	Texture2DPtr snowTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/snow.png");

	MeshPtr fighterShip = resourceManager.createMeshFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj");
	InstancedMeshPtr statueMesh = resourceManager.createInstancedMeshFromFile("Resources/Meshes/SM_Prop_Statue_01.obj");

	ShaderPtr meshShader = graphicsEngine.createShader({
			"MeshShader",
			"MeshShader"
		});
	ShaderPtr terrainShader = graphicsEngine.createShader({
			"TerrainShader",
			"TerrainShader"
		});

	m_outlineShader = graphicsEngine.createShader({
			"OutlineShader",
			"OutlineShader"
		});

	ShaderPtr instancedMeshShader = graphicsEngine.createShader({
			"InstancedMesh",
			"InstancedMesh"
		});


	m_ship = m_entitySystem->createEntity<MeshEntity>();
	m_ship->setScale(Vector3(0.05f));
	m_ship->setPosition(Vector3(0, 40, 0));
	m_ship->setShininess(64.0f);
	m_ship->setTexture(sciFiSpaceTexture2D);
	m_ship->setReflectiveMapTexture(shipReflectiveMap);
	m_ship->setMesh(fighterShip);
	m_ship->setShader(meshShader);
	m_ship->setShadowShader(m_shadowShader);
	m_ship->setGeometryShader(m_meshGeometryShader);
	//m_ship->setLightingShader(m_meshLightingShader);

	HeightMapInfo buildInfo = { "Resources/Heightmaps/Heightmap0.raw", 256, 256, 4.0f };
	HeightMapPtr heightmap = resourceManager.createHeightMap(buildInfo);

	m_terrain = m_entitySystem->createEntity<TerrainEntity>();
	m_terrain->generateTerrainMesh(heightmap);
	m_terrain->setPosition(Vector3(0, -10, 0));
	m_terrain->setTexture(grassTexture);
	m_terrain->setTexture1(dirtTexture);
	m_terrain->setTexture2(stoneTexture);
	m_terrain->setTexture3(snowTexture);
	m_terrain->setHeightMap(heightMapTexture);
	m_terrain->setShader(terrainShader);
	m_terrain->setShadowShader(m_shadowShader);
	m_terrain->setGeometryShader(m_terrainGeometryShader);

	//Creating instanced tree obj
	auto statues = m_entitySystem->createEntity<InstancedMeshEntity>();
	statues->setShininess(32.0f);
	statues->setTexture(ancientWorldsTexture2D);
	statues->setShader(instancedMeshShader);
	statues->setMesh(statueMesh);
	statues->setReflectiveMapTexture(shipReflectiveMap); //this is wrong
	statues->setShadowShader(m_shadowInstancedShader);
	statues->setGeometryShader(m_instancedmeshGeometryShader);
	//statues->setLightingShader(m_meshLightingShader);


	//adds instances to the instanced mine mesh
	float spacing = 75.0f;
	for (int row = -4; row < 4; ++row) {
		for (int col = -4; col < 4; ++col) {
			// Calculate the position of the current tree based on the grid and spacing
			Vector3 position = Vector3(col * spacing, 0, row * spacing);

			if (position == Vector3(0.0f)) break;

			// Generate random rotation angles
			float angleY = randomNumber(360.0f);

			// Add the tree instance with random rotations
			statueMesh->addInstance(position, Vector3(0.2f), Vector3(0, angleY, 0));
		}
	}

	//Init instance buffer
	statueMesh->initInstanceBuffer();

	// Create and initialize a DirectionalLight struct
	//DirectionalLight directionalLight1;
	//directionalLight1.Direction = Vector3(0.0f, -1.0f, -0.5f);
	//directionalLight1.Color = Vector3(0.1f);
	//directionalLight1.SpecularStrength = 0.1f;
	//lightManager.createDirectionalLight(directionalLight1);

	// Create and initialize a DirectionalLight struct
	//DirectionalLight directionalLight2;
	//directionalLight2.Direction = Vector3(0.0f, -1.0f, 0.5f);
	//directionalLight2.Color = Vector3(0.1f);
	//directionalLight2.SpecularStrength = 0.1f;
	//lightManager.createDirectionalLight(directionalLight2);

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
	lightManager.setSpotlightStatus(false);
	
	float pointLightSpacing = 100.0f;
	int gridRows = 3; // Number of rows in the grid
	int gridCols = 4; // Number of columns in the grid

	// Initialize 10 point lights in a 4x5 grid
	for (int row = 0; row < gridRows; ++row) {
		for (int col = 0; col < gridCols; ++col) {
			// Create a new point light entity
			auto pointLightObject = new MeshEntity();
			pointLightObject->onCreate();
			pointLightObject->setTransparency(0.75f);
			m_lights.push_back(pointLightObject);

			// Randomly set color to either red or blue
			int randomColorChoice = (int)randomNumber(2.0f); // Generates 0 or 1
			Vector3 lightColor = (randomColorChoice == 0) ? Color::Red * 2.0f : Color::Blue * 2.0f;
			pointLightObject->setColor(lightColor);

			// Calculate the position based on row and column, center the grid around (0,0)
			float xPosition = (col - gridCols / 2) * pointLightSpacing; // Center horizontally
			float yPosition = 15.0f; // Fixed Y position
			float zPosition = (row - gridRows / 2) * pointLightSpacing; // Center vertically
			pointLightObject->setPosition(Vector3(xPosition, yPosition, zPosition));
			pointLightObject->setScale(Vector3(3.0f));
			// Set mesh and shaders
			pointLightObject->setMesh(gameOwner->getSphereMesh());
			pointLightObject->setShader(m_solidColorMeshShader);
			pointLightObject->setShadowShader(m_shadowShader);
			pointLightObject->setGeometryShader(m_meshGeometryShader);

			// Configure point light properties
			PointLight pointLight;
			pointLight.Position = pointLightObject->getPosition();
			pointLight.Color = pointLightObject->getColor();
			pointLight.SpecularStrength = 1.0f;
			pointLight.AttenuationConstant = 1.0f;
			pointLight.AttenuationLinear = 0.022f;
			pointLight.AttenuationExponent = 0.0019f;

			// Add the point light to the light manager
			lightManager.createPointLight(pointLight);
		}
	}

	//create point lights and dont forget these lines
	//m_ship->setGeometryShader(m_meshGeometryShader);
	//m_ship->setLightingShader(m_meshLightingShader);
}

void Scene2::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;

	// Convert the Euler angles to a quaternion
	Quaternion shipRotation = Quaternion(glm::radians(glm::vec3(0.0f, m_elapsedSeconds * 10.0f, 0.0f)));

	// Set the rotations using quaternions
	m_ship->setRotation(shipRotation);
}

void Scene2::onFixedUpdate(float _fixedDeltaTime)
{
	Scene::onFixedUpdate(_fixedDeltaTime);
}

void Scene2::onLateUpdate(float deltaTime)
{
	Scene::onLateUpdate(deltaTime);
}

void Scene2::onQuit()
{
	Scene::onQuit();
}