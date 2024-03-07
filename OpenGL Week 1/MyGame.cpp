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

	//loading texture resources
	auto cobblestone = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/cobblestone.png"));
	auto sky = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/sky.jpg"));
	auto lava = std::dynamic_pointer_cast<Texture>(getResourceManager()->createResourceFromFile(L"Resources/Textures/lava.jpg"));

	//loading model resources
	auto teapot = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/teapot.obj"));
	auto sphere = std::dynamic_pointer_cast<Mesh>(getResourceManager()->createResourceFromFile(L"Resources/Meshes/sphere.obj"));

	m_meshShader = m_graphicsEngine->createShaderProgram({
			L"MeshShader",
			L"MeshShader"
		});

	m_skyboxShader = m_graphicsEngine->createShaderProgram(
	{
		L"SkyBoxShader",
		L"SkyBoxShader"
	});

	//creating skybox
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(1000, 1000, 1000));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(sky);
		entity->setMesh(sphere);
		entity->setShader(m_skyboxShader);
		m_skybox = entity;
	}
	//creating the floor
	{
		auto cube = getEntitySystem()->createEntity<CubeEntity>();
		cube->setScale(glm::vec3(2.0f, 0.1f, 2.0f));
		cube->setPosition(glm::vec3(0, -1, 0));
		cube->setTexture(lava); 
	}

	//creating teapot
	{
		auto entity = getEntitySystem()->createEntity<MeshEntity>();
		entity->setScale(glm::vec3(1, 1, 1));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setTexture(lava);
		entity->setMesh(teapot);
		entity->setShader(m_meshShader);
	}
	

	srand((unsigned int)time(NULL));
	for (auto y = -4; y < 4; y++)
	{
		for (auto x = -4; x < 4; x++)
		{

			auto cube = getEntitySystem()->createEntity<CubeEntity>();

			auto roty = (rand() % 600) + (200.0f);
			roty /= 1000.0f;
			auto width = (rand() % 600) + (200.0f);
			width /= 1000.0f;

			auto height = width;


			cube->setScale(glm::vec3(width, height, width));
			cube->setPosition(glm::vec3(x * 1.4f, (height / 2.0f) - 3.5f, y * 1.4f));
			cube->setRotation(glm::vec3(0, roty, 0));
			cube->setTexture(cobblestone);
		}
	}
	
	//adding white light
	{
		auto entity = getEntitySystem()->createEntity<LightEntity>();
		entity->setRotation(glm::vec3(-0.707f, 0, 0.0f));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setColor(glm::vec4(1, 1, 1, 1));

		m_light = entity;
	}

	//adding red light
	{
		auto entity = getEntitySystem()->createEntity<LightEntity>();
		entity->setRotation(glm::vec3(-0.707f, 0, 0.0f));
		entity->setPosition(glm::vec3(0, 0, 0));
		entity->setColor(glm::vec4(1, 0, 0, 1));

		m_lightred = entity;
	}
	//creating the player
	//all the input managements, creation of camera etc. are moved inside Player class
	auto m_player = getEntitySystem()->createEntity<MyPlayer>();
	m_player->setPosition(glm::vec3(0, 0, 0));

	//enabling play mode
	getInputManager()->enablePlayMode(true);
}

void MyGame::onUpdate(float deltaTime)
{
	m_roty += 0.57f * deltaTime;

	//rotating light and skybox together
	//m_light->setRotation(glm::vec3(-0.707f, m_roty, 0));
	//m_skybox->setRotation(glm::vec3(0, 0.1 * m_roty, 0));
}
