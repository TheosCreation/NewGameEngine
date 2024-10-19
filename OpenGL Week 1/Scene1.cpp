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

#include "Scene1.h"
#include "MyPlayer.h"
#include "Game.h"

Scene1::Scene1(Game* game) : Scene(game)
{
}

Scene1::~Scene1()
{
}

void Scene1::onCreate()
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

	auto ship2 = m_entitySystem->createEntity<MeshEntity>();
	ship2->setScale(Vector3(0.05f));
	ship2->setPosition(Vector3(0, 70, 0));
	ship2->setShininess(64.0f);
	ship2->setTexture(sciFiSpaceTexture2D);
	ship2->setReflectiveMapTexture(shipReflectiveMap);
	ship2->setMesh(fighterShip);
	ship2->setShader(meshShader);
	ship2->setShadowShader(m_shadowShader);
	ship2->setGeometryShader(m_meshGeometryShader);
	//ship2->setLightingShader(m_meshLightingShader);

	HeightMapInfo buildInfo = { "Resources/Heightmaps/Heightmap0.raw", 512, 512, 5.0f };
	HeightMapPtr heightmap = resourceManager.createHeightMap(buildInfo);

	m_terrain = m_entitySystem->createEntity<TerrainEntity>();
	m_terrain->generateTerrainMesh(heightmap);
	m_terrain->setPosition(Vector3(0, -50, 0));
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
	float spacing = 50.0f;
	for (int row = -4; row < 4; ++row) {
		for (int col = -4; col < 4; ++col) {
			// Calculate the position of the current tree based on the grid and spacing
			Vector3 position = Vector3(col * spacing, 0, row * spacing);

			if (position == Vector3(0.0f)) break;

			// Generate random rotation angles
			float angleY = randomNumber(360.0f);

			float randomScale = randomNumber(0.15f);

			// Add the tree instance with random rotations
			statueMesh->addInstance(position, Vector3(0.05f + randomScale), Vector3(0, angleY, 0));
		}
	}

	//Init instance buffer
	statueMesh->initInstanceBuffer();

	// Create and initialize DirectionalLight struct
	DirectionalLight directionalLight;
	directionalLight.Direction = Vector3(0.0f, -1.0f, -0.3f);
	directionalLight.Color = Vector3(0.5f);
	directionalLight.SpecularStrength = 0.1f;
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
	lightManager.setSpotlightStatus(false);

	//create point lights and dont forget these lines
	//m_ship->setGeometryShader(m_meshGeometryShader);
	//m_ship->setLightingShader(m_meshLightingShader);

}

void Scene1::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;


	// Convert the Euler angles to a quaternion
	Quaternion shipRotation = Quaternion(glm::radians(glm::vec3(0.0f, m_elapsedSeconds * 10.0f, 0.0f)));

	// Set the rotations using quaternions
	m_ship->setRotation(shipRotation);
}

void Scene1::onFixedUpdate(float _fixedDeltaTime)
{
	Scene::onFixedUpdate(_fixedDeltaTime);
}

void Scene1::onLateUpdate(float deltaTime)
{
	Scene::onLateUpdate(deltaTime);
}

void Scene1::onGraphicsUpdate(float deltaTime)
{
}

void Scene1::onQuit()
{
	Scene::onQuit();
}