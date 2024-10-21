/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene4.cpp
Description : Scene4 class is a stripped-down class of the scene class to allow end user to create their own entities.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Scene4.h"
#include "MyPlayer.h"
#include "Game.h"
#include "GeometryBuffer.h"
#include "Framebuffer.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "LightManager.h"

Scene4::Scene4(Game* game) : Scene(game)
{
}

Scene4::~Scene4()
{
}

void Scene4::onCreate()
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

	HeightMapInfo buildInfo = { "Resources/Heightmaps/Heightmap0.raw", 512, 512, 4.0f };
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

}

void Scene4::onUpdate(float deltaTime)
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


void Scene4::onFixedUpdate(float _fixedDeltaTime)
{
	Scene::onFixedUpdate(_fixedDeltaTime);
}

void Scene4::onLateUpdate(float deltaTime)
{
	Scene::onLateUpdate(deltaTime);
}

void Scene4::onGraphicsUpdate()
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

void Scene4::onQuit()
{
	Scene::onQuit();
}