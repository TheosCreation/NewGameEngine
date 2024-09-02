/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Scene3.cpp
Description : 
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Scene3.h"
#include "MyPlayer.h"
#include "Game.h"
#include "PerlinNoise.h"
#include <fstream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Scene3::Scene3(Game* game) : Scene(game)
{
}

Scene3::~Scene3()
{
}

void Scene3::onCreate()
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

    // Define the width and height of the image
    const unsigned int Width = 512;
    const unsigned int Height = 512;

    // Create a pixel array to store the noise values
    uint8_t* Pixels = new uint8_t[Width * Height];
    int Index = 0;

    // Create an instance of the PerlinNoise class
    PerlinNoise noiseGenerator; //will init the seed in the contructor

    float minNoise = std::numeric_limits<float>::max();
    float maxNoise = std::numeric_limits<float>::lowest();

    // First pass to find min and max noise values
    for (unsigned int Col = 0; Col < Height; Col++)
    {
        for (unsigned int Row = 0; Row < Width; Row++)
        {
            float Noise = static_cast<float>(noiseGenerator.TotalNoisePerPoint(Row, Col));
            minNoise = glm::min(minNoise, Noise);
            maxNoise = glm::max(maxNoise, Noise);
        }
    }

    // Second pass to apply normalization
    for (unsigned int Col = 0; Col < Height; Col++)
    {
        for (unsigned int Row = 0; Row < Width; Row++)
        {
            float Noise = static_cast<float>(noiseGenerator.TotalNoisePerPoint(Row, Col));

            // Normalize the noise value to the [0, 255] range
            Noise = ((Noise - minNoise) / (maxNoise - minNoise)) * 255.0f;
            Noise = glm::clamp(Noise, 0.0f, 255.0f);

            Pixels[Index++] = static_cast<uint8_t>(Noise);
        }
    }

    // Create the RAW file
    string savePathRaw = "Resources/Heightmaps/" + ToString(noiseGenerator.Seed) + ".raw";
    std::ofstream RawFile(savePathRaw, std::ios_base::binary);
    if (RawFile)
    {
        RawFile.write(reinterpret_cast<char*>(Pixels), static_cast<std::streamsize>(Width * Height));
        RawFile.close();
    }

    string savePathJpg = "Resources/Textures/Noise/" + ToString(noiseGenerator.Seed) + ".jpg";
    stbi_write_jpg(savePathJpg.c_str(), Width, Height, 1, Pixels, 100);

    // Clean up the allocated memory
    delete[] Pixels;

    HeightMapInfo buildInfo = { savePathRaw, 512, 512, 1.0f };
    HeightMapPtr heightmap = resourceManager.createHeightMap(buildInfo);

    ShaderPtr terrainShader = graphicsEngine.createShader({
            "TerrainShader",
            "TerrainShader"
        });
    
    ShaderPtr quadShader = graphicsEngine.createShader({
            "QuadShader",
            "QuadShader"
        });
    ShaderPtr quadBlendedShader = graphicsEngine.createShader({
            "QuadShader",
            "QuadBlendingShader"
        });

    Texture2DPtr grassTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/grass.png");
    Texture2DPtr dirtTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/dirt.png");
    Texture2DPtr stoneTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/stone.png");
    Texture2DPtr snowTexture = resourceManager.createTexture2DFromFile("Resources/Textures/Terrain/snow.png");

    Texture2DPtr perlinNoise = resourceManager.createTexture2DFromFile(savePathJpg);

    auto quad1 = m_entitySystem->createEntity<QuadEntity>();
    quad1->setPosition(Vector3(100, 0, -300));
    quad1->setScale(Vector3(100.0f));
    quad1->setTexture(grassTexture);
    quad1->setTexture1(dirtTexture);
    quad1->setHeightMap(perlinNoise);
    quad1->setShader(quadBlendedShader);

    auto quad2 = m_entitySystem->createEntity<QuadEntity>();
    quad2->setPosition(Vector3(-100, 0, -300));
    quad2->setScale(Vector3(100.0f));
    quad2->setTexture(perlinNoise);
    quad2->setShader(quadShader);

    m_terrain = m_entitySystem->createEntity<TerrainEntity>();
    m_terrain->generateTerrainMesh(heightmap);
    m_terrain->setPosition(Vector3(0, -500, 0));
    m_terrain->setTexture(grassTexture);
    m_terrain->setTexture1(dirtTexture);
    m_terrain->setTexture2(stoneTexture);
    m_terrain->setTexture3(snowTexture);
    m_terrain->setShader(terrainShader);

	// Create and initialize DirectionalLight struct
	DirectionalLight directionalLight;
	directionalLight.Direction = Vector3(0.5f, -1.0f, -0.5f);
	directionalLight.Color = Vector3(0.9f);
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

void Scene3::onUpdate(float deltaTime)
{
	Scene::onUpdate(deltaTime);
	m_elapsedSeconds += deltaTime;
}

void Scene3::onFixedUpdate(float _fixedDeltaTime)
{
	Scene::onFixedUpdate(_fixedDeltaTime);
}

void Scene3::onLateUpdate(float deltaTime)
{
	Scene::onLateUpdate(deltaTime);
}

void Scene3::onQuit()
{
	Scene::onQuit();
}