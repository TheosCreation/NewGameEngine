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
#include "GeometryBuffer.h"
#include "Framebuffer.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "LightManager.h"

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
	Texture2DPtr grassTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/stone.png");
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
	m_terrain->setPosition(Vector3(0, -20, 0));
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

			// Add the tree instance with random rotations
			statueMesh->addInstance(position, Vector3(0.2f), Vector3(0, angleY, 0));
		}
	}

	//Init instance buffer
	statueMesh->initInstanceBuffer();

	// Create and initialize a DirectionalLight struct
	DirectionalLight directionalLight1;
	directionalLight1.Direction = Vector3(0.0f, -1.0f, -0.5f);
	directionalLight1.Color = Vector3(0.6f);
	directionalLight1.SpecularStrength = 0.1f;
	lightManager.createDirectionalLight(directionalLight1);

	// Create and initialize a DirectionalLight struct
	DirectionalLight directionalLight2;
	directionalLight2.Direction = Vector3(0.0f, -1.0f, 0.5f);
	directionalLight2.Color = Vector3(0.6f);
	directionalLight2.SpecularStrength = 0.1f;
	lightManager.createDirectionalLight(directionalLight2);

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

	float pointLightSpacing = 30.0f;
	// Initialize 2 point lights
	for (int i = 0; i < 2; i++) {
		// Create a new point light entity
		auto pointLightObject = m_entitySystem->createEntity<MeshEntity>();
		pointLightObject->setTransparency(0.75f);

		// Randomly set color to either red or blue
		int randomColorChoice = (int)randomNumber(2.0f); // Generates 0 or 1
		Vector3 lightColor = (randomColorChoice == 0) ? Color::Red * 2.0f : Color::Blue * 2.0f;
		pointLightObject->setColor(lightColor);

		// Calculate the position based on row and column, center the grid around (0,0)
		float xPosition = i * pointLightSpacing; // Center horizontally
		float yPosition = 15.0f; // Fixed Y position
		float zPosition = 0;
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

	//create point lights and dont forget these lines
	//m_ship->setGeometryShader(m_meshGeometryShader);
	//m_ship->setLightingShader(m_meshLightingShader);

}

void Scene1::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;

	// Parameters for the circular path
	float radius = 50.0f; // Radius of the circle
	float speed = 1.0f;   // Speed of the ship's movement

	// Calculate the position on the circular path
	float angle = m_elapsedSeconds * speed; // Angle in radians
	float x = radius * cos(angle);
	float z = radius * sin(angle);

	// Update the ship's position
	m_ship->setPosition(glm::vec3(x, 50.0f, z));

	// Make the ship face the direction it's moving by calculating the forward vector
	glm::vec3 forward = glm::normalize(glm::vec3(-sin(angle), 0.0f, cos(angle)));

	// Convert the forward vector to a rotation quaternion
	Quaternion shipRotation = QuaternionUtils::LookAt(forward, glm::vec3(0.0f, 1.0f, 0.0f));

	// Set the ship's rotation
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

void Scene1::onGraphicsUpdate()
{

	auto& lightManager = LightManager::GetInstance();
	auto& graphicsEngine = GraphicsEngine::GetInstance();

	//m_postProcessingFramebuffer->Bind();
	//graphicsEngine.clear(glm::vec4(0, 0, 0, 1));
	
	UniformData data = {};
	data.currentTime = gameOwner->GetCurrentTime();
	for (auto& camera : m_entitySystem->getCameras())
	{
		if (camera->getCameraType() == CameraType::Perspective)
		{
			camera->getViewMatrix(data.viewMatrix);
			camera->getProjectionMatrix(data.projectionMatrix);
			data.cameraPosition = camera->getPosition();
			lightManager.setSpotlightPosition(data.cameraPosition);
			lightManager.setSpotlightDirection(camera->getForwardDirection());
		}
		else
		{
			camera->getViewMatrix(data.uiViewMatrix);
			camera->getProjectionMatrix(data.uiProjectionMatrix);
		}
	}

	for (uint i = 0; i < lightManager.getDirectionalLightCount(); i++)
	{
		//Shadow Pass
		lightManager.BindShadowMap(i);
		m_entitySystem->onShadowPass(i);
		lightManager.UnBindShadowMap(i);
	}

	graphicsEngine.setViewport(gameOwner->getWindow()->getInnerSize());

	graphicsEngine.clear(glm::vec4(0, 0, 0, 1));
	m_entitySystem->onGraphicsUpdate(data);
	m_skyBox->onGraphicsUpdate(data);
	//m_postProcessingFramebuffer->UnBind();



	//graphicsEngine.clear(glm::vec4(0, 0, 0, 1)); //clear the scene
	//NewUniformData uniformData;
	//uniformData.CreateData<float>("Time", m_currentTime);
	//uniformData.CreateData<Vector2>("Resolution", m_display->getInnerSize());
	//if (currentTexture1)
	//{
	//	//if the current shader needs a second texture we pass that into it
	//	NewExtraTextureData textureData;
	//	textureData.AddTexture("Texture1", currentTexture1, 1);
	//	m_canvasQuad->onGraphicsUpdate(uniformData, textureData);
	//}
	//else
	//{
	//	m_canvasQuad->onGraphicsUpdate(uniformData);
	//}
	//
}

void Scene1::onQuit()
{
	Scene::onQuit();
}