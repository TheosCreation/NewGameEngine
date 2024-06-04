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

	// create a cube map texture and set the texture of the skybox to the cubemap texture
	std::vector<std::string> skyboxCubeMapTextureFilePaths;
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Right.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Left.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Top.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Bottom.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Back.png");
	skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Front.png");
	TextureCubeMapPtr skyBoxTexture = getResourceManager()->createCubeMapTextureFromFile(skyboxCubeMapTextureFilePaths);

	m_skyBox->setTexture(skyBoxTexture);


	//Loading texture resources
	Texture2DPtr buttonDownTexture = getResourceManager()->createTexture2DFromFile("Resources/Textures/Button_Down.png");
	Texture2DPtr buttonHoveringTexture = getResourceManager()->createTexture2DFromFile("Resources/Textures/Button_Hovering.png");
	Texture2DPtr buttonUpTexture = getResourceManager()->createTexture2DFromFile("Resources/Textures/Button_Up.png");

	Texture2DPtr plainAncientTextureSheet = getResourceManager()->createTexture2DFromFile("Resources/Textures/PolygonAncientWorlds_Statue_01.png");
	
	Texture2DPtr sciFiSpace = getResourceManager()->createTexture2DFromFile("Resources/Textures/PolygonSciFiSpace_Texture_01_A.png");
	Texture2DPtr shipReflectiveMap = getResourceManager()->createTexture2DFromFile("Resources/Textures/ReflectionMap_White.png");
	

	//Loading meshes
	MeshPtr fighterShip = getResourceManager()->createMeshFromFile("Resources/Meshes/Space/SM_Ship_Fighter_02.obj");
	InstancedMeshPtr mineMesh = getResourceManager()->createInstancedMeshFromFile("Resources/Meshes/Space/SM_Prop_Mine_01.obj");
	
	//Loading Shader
	ShaderPtr quadShader = m_graphicsEngine->createShader({
			L"QuadShader",
			L"QuadShader"
		});
	ShaderPtr meshShader = m_graphicsEngine->createShader({
			L"MeshShader",
			L"MeshShader"
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
	m_player->setInstancedEntity(m_instanceMines, sciFiSpace, plainAncientTextureSheet);
	m_player->setButtonTextures(buttonUpTexture, buttonHoveringTexture, buttonDownTexture);

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
		m_lightManager->createPointLight(pointLight);
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

void MyGame::onFixedUpdate()
{
}

void MyGame::onLateUpdate(float deltaTime)
{
}