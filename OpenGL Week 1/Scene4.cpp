/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene4.cpp
Description : A stripped-down class of the scene class to allow end user to create their own entities.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Scene4.h"
#include "MyPlayer.h"
#include "Game.h"

Scene4::Scene4(Game* game) : Scene(game)
{
}

Scene4::~Scene4()
{
}

void Scene4::onCreate()
{
	Scene::onCreate();
	auto& resourceManager = ResourceManager::GetInstance();
	auto& lightManager = LightManager::GetInstance();
	auto& graphicsEngine = GraphicsEngine::GetInstance();

	gameOwner->SetFullScreenShader();

	// Loading texture resources
	Texture2DPtr sciFiSpace = resourceManager.createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
	Texture2DPtr shipReflectiveMap = resourceManager.createTexture2DFromFile("Resources/Textures/ReflectionMap_White.png");
	m_oldRipple = resourceManager.createTexture2DFromFile("Resources/Textures/old.png");
	m_grayNoiseSmall = resourceManager.createTexture2DFromFile("Resources/Textures/grayNoiseSmall.png");

	// Loading mesh resources
	MeshPtr fighterShip = resourceManager.createMeshFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj");
	InstancedMeshPtr mineMesh = resourceManager.createInstancedMeshFromFile("Resources/Meshes/Space/SM_Prop_Mine_01.obj");

	// Loading Shaders
	ShaderPtr meshShader = graphicsEngine.createShader({
			"MeshShader",
			"MeshShader"
		});
	ShaderPtr instancedMeshShader = graphicsEngine.createShader({
			"InstancedMesh",
			"InstancedMesh"
		});

	ShaderPtr colorInversionShader = graphicsEngine.createShader({
			"ScreenQuad",
			"InvertColorFullRenderPass"
		});
	m_fullScreenShaders.push_back(colorInversionShader);

	ShaderPtr grayScaleLuminosityShader = graphicsEngine.createShader({
			"ScreenQuad",
			"GreyScaleLuminosityFullRenderPass"
		});
	m_fullScreenShaders.push_back(grayScaleLuminosityShader);

	ShaderPtr rainShader = graphicsEngine.createShader({
			"ScreenQuad",
			"RainFullRenderPass"
		});
	m_fullScreenShaders.push_back(rainShader);

	ShaderPtr crtShader = graphicsEngine.createShader({
			"ScreenQuad",
			"MattiasCRTRenderPass"
		});
	m_fullScreenShaders.push_back(crtShader);

	ShaderPtr chromaticAberration = graphicsEngine.createShader({
			"ScreenQuad",
			"ChromaticAberrationRenderPass"
		});
	m_fullScreenShaders.push_back(chromaticAberration);

	ShaderPtr oldFilmShader = graphicsEngine.createShader({
			"ScreenQuad",
			"OldFilmRenderPass"
		});
	m_fullScreenShaders.push_back(oldFilmShader);

	ShaderPtr scanLinesShader = graphicsEngine.createShader({
			"ScreenQuad",
			"ScanLineFullRenderPass"
		});
	m_fullScreenShaders.push_back(scanLinesShader);

	// Creating a ship
	m_ship = m_entitySystem->createEntity<MeshEntity>();
	m_ship->setScale(Vector3(0.05f));
	m_ship->setPosition(Vector3(0, 0, 0));
	m_ship->setShininess(32.0f);
	m_ship->setTexture(sciFiSpace);
	m_ship->setReflectiveMapTexture(shipReflectiveMap);
	m_ship->setMesh(fighterShip);
	m_ship->setShader(meshShader);
	m_ship->setShadowShader(m_shadowShader);

	// Creating a instanced mine obj
	m_instanceMines = m_entitySystem->createEntity<InstancedMeshEntity>();
	m_instanceMines->setShininess(32.0f);
	m_instanceMines->setTexture(sciFiSpace);
	m_instanceMines->setShader(instancedMeshShader);
	m_instanceMines->setMesh(mineMesh);
	m_instanceMines->setReflectiveMapTexture(shipReflectiveMap);
	m_instanceMines->setShadowShader(m_shadowShader);


	// Adds instances to the instanced mine mesh
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

	// Init instance buffer
	mineMesh->initInstanceBuffer();

	// Creating the player object
	// all the input managements, creation of camera are inside Player class
	m_player = m_entitySystem->createEntity<MyPlayer>();
	m_player->setScale(Vector3(0.0f));
	m_player->setPosition(Vector3(0.0f, 20.0f, 0.0f));

	// Create and initialize a DirectionalLight
	DirectionalLight directionalLight;
	directionalLight.Direction = Vector3(0.5f, -1.0f, -0.5f);
	directionalLight.Color = Vector3(0.1f);
	directionalLight.SpecularStrength = 0.5f;
	lightManager.createDirectionalLight(directionalLight);

	// Create and initialize a SpotLight
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

void Scene4::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);
	auto& inputManager = InputManager::GetInstance();
	if (inputManager.isKeyPressed(Key::KeyTab))
	{
		switchFullscreenShader();
	}
	m_elapsedSeconds += deltaTime;


	// Convert the Euler angles to a quaternion
	Quaternion shipRotation = Quaternion(glm::radians(glm::vec3(0.0f, m_elapsedSeconds * 10.0f, 0.0f)));

	// Set the rotations using quaternions
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

void Scene4::onQuit()
{
	Scene::onQuit();
}

void Scene4::switchFullscreenShader()
{
	// Increment the current index and wrap it around
	currentIndex = (currentIndex + 1) % (m_fullScreenShaders.size() + 1); // +1 to include the default shader

	if (currentIndex < m_fullScreenShaders.size())
	{
		// Check which shader is currently active and set the appropriate texture
		if (m_fullScreenShaders[currentIndex] == m_fullScreenShaders[2])
		{
			gameOwner->SetFullScreenShader(m_fullScreenShaders[currentIndex], m_grayNoiseSmall);
		}
		else if (m_fullScreenShaders[currentIndex] == m_fullScreenShaders[5])
		{
			gameOwner->SetFullScreenShader(m_fullScreenShaders[currentIndex], m_oldRipple);
		}
		else
		{
			gameOwner->SetFullScreenShader(m_fullScreenShaders[currentIndex]);
		}
	}
	else
	{
		// Reset to the default shader after reaching the max index
		gameOwner->SetFullScreenShader();
		currentIndex = -1; // Set to -1 so the next increment starts from 0
	}
}