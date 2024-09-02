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

	Texture2DPtr sciFiSpace = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
	MeshPtr fighterShip = resourceManager.createMeshFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj");


	Texture2DPtr shipReflectiveMap = resourceManager.createTexture2DFromFile("Resources/Textures/ReflectionMap_White.png");

	ShaderPtr meshShader = graphicsEngine.createShader({
			"MeshShader",
			"MeshShader"
		});

	m_outlineShader = graphicsEngine.createShader({
			"OutlineShader",
			"OutlineShader"
		}); 


	m_ship = m_entitySystem->createEntity<MeshEntity>();
	m_ship->setScale(Vector3(0.05f));
	m_ship->setPosition(Vector3(0, 0, 0));
	m_ship->setShininess(32.0f);
	m_ship->setTexture(sciFiSpace);
	m_ship->setReflectiveMapTexture(shipReflectiveMap);
	m_ship->setMesh(fighterShip);
	m_ship->setShader(meshShader);
	m_ship->setShadowShader(m_shadowShader);

	auto secondShip = m_entitySystem->createEntity<MeshEntity>();
	secondShip->setScale(Vector3(0.1f));
	secondShip->setPosition(Vector3(0, -100, 0));
	secondShip->setShininess(32.0f);
	secondShip->setTexture(sciFiSpace);
	secondShip->setReflectiveMapTexture(shipReflectiveMap);
	secondShip->setMesh(fighterShip);
	secondShip->setShader(meshShader);
	secondShip->setShadowShader(m_shadowShader);

	// Create and initialize DirectionalLight struct
	DirectionalLight directionalLight;
	directionalLight.Direction = Vector3(0.5f, -1.0f, -0.5f);
	directionalLight.Color = Vector3(0.1f);
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
	auto& graphicsEngine = GraphicsEngine::GetInstance();
	auto& lightManager = LightManager::GetInstance();

	graphicsEngine.clear(glm::vec4(0, 0, 0, 1));
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

	// Render skybox
	ShaderPtr skyboxShader = m_skyBox->getShader();
	graphicsEngine.setShader(skyboxShader);
	m_skyBox->onGraphicsUpdate(data);

	graphicsEngine.setStencil(StencilOperationType::Set);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	
	m_entitySystem->onGraphicsUpdate(deltaTime, data);
	
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	
	for (auto& graphicEntity : m_entitySystem->getGraphicsEntities())
	{
		ShaderPtr originalShader = graphicEntity->getShader();
	    graphicEntity->setShader(m_outlineShader);
	    graphicEntity->onGraphicsUpdate(data);
	    graphicEntity->setShader(originalShader);
	}

	m_entitySystem->onGraphicsUpdate(deltaTime, data);
	
	glDisable(GL_STENCIL_TEST);
	graphicsEngine.setStencil(StencilOperationType::ResetAlways);
}

void Scene1::onQuit()
{
	Scene::onQuit();
}