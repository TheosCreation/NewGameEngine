#include "Scene.h"
#include "SSRQuad.h"
#include "GeometryBuffer.h"

Scene::Scene(Game* game)
{
    gameOwner = game;
    m_shadowMap = std::make_unique<ShadowMap>(Vector2(4096.0f));
    m_postProcessingFramebuffer = std::make_unique<Framebuffer>(gameOwner->getWindow()->getInnerSize());
}

Scene::~Scene()
{
}

void Scene::onShadowPass()
{
    
}

void Scene::onGeometryPass()
{
    auto& lightManager = LightManager::GetInstance();

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


    m_entitySystem->onGeometryPass(data);
}

void Scene::onLightingPass()
{
    auto& lightManager = LightManager::GetInstance();

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
    gameOwner->getScreenSpaceQuad()->onLightingPass(data);
    //m_skyBox->onLightingPass(data);

    //m_entitySystem->onLightingPass(data);
}

void Scene::onGraphicsUpdate(float deltaTime)
{
    //Geometry Pass
    auto& geometryBuffer = GeometryBuffer::GetInstance();
    geometryBuffer.Bind();
    onGeometryPass();
    geometryBuffer.UnBind();

    //Shadow Pass
    m_shadowMap->Bind();
    m_entitySystem->onShadowPass(0);
    m_shadowMap->UnBind();

    GraphicsEngine::GetInstance().setViewport(gameOwner->getWindow()->getInnerSize());

    onLightingPass();

    geometryBuffer.WriteDepth();

    auto& lightManager = LightManager::GetInstance();
    lightManager.setShadowMapTexture1(m_shadowMap);

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

    m_skyBox->onGraphicsUpdate(data);
}

void Scene::onCreate()
{
    auto& resourceManager = ResourceManager::GetInstance();
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    m_entitySystem = std::make_unique<EntitySystem>(this);

    //Creating skybox object
    m_skyBox = std::make_unique<SkyboxEntity>();
    ShaderPtr skyboxShader = graphicsEngine.createShader({
            "SkyBoxShader",
            "SkyBoxShader"
        });

    m_solidColorMeshShader = graphicsEngine.createShader({
            "SolidColorMesh",
            "SolidColorMesh"
        }); 
    
    m_shadowShader = graphicsEngine.createShader({
            "ShadowShader",
            "ShadowShader"
        });
    
    m_shadowInstancedShader = graphicsEngine.createShader({
            "ShadowShaderInstanced",
            "ShadowShader"
        });

    m_skyboxGeometryShader = graphicsEngine.createShader({
            "SkyBoxShader",
            "GeometryPassSkybox"
        });
    m_meshGeometryShader = graphicsEngine.createShader({
            "MeshShader",
            "GeometryPass"
        });
    m_instancedmeshGeometryShader = graphicsEngine.createShader({
            "InstancedMesh",
            "GeometryPass"
        });
    
    m_terrainGeometryShader = graphicsEngine.createShader({
            "TerrainShader",
            "GeometryPassTerrian"
        });
    
    //m_meshLightingShader = graphicsEngine.createShader({
    //        "MeshShader",
    //        "MeshLightingShader"
    //    });

    m_skyBox->setEntitySystem(m_entitySystem.get());
    m_skyBox->setMesh(gameOwner->getCubeMesh());
    m_skyBox->setShader(skyboxShader);
    m_skyBox->setGeometryShader(m_skyboxGeometryShader);
    //m_skyBox->setLightingShader(m_meshLightingShader);

    // create a cube map texture and set the texture of the skybox to the cubemap texture
    std::vector<std::string> skyboxCubeMapTextureFilePaths;
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Right.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Left.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Top.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Bottom.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Back.png");
    skyboxCubeMapTextureFilePaths.push_back("Resources/Textures/RedEclipse/Front.png");
    TextureCubeMapPtr skyBoxTexture = resourceManager.createCubeMapTextureFromFile(skyboxCubeMapTextureFilePaths);
    m_skyBox->setTexture(skyBoxTexture);
}

void Scene::onCreateLate()
{
    for (auto& camera : m_entitySystem->getCameras())
    {
        // Set the screen area for all cameras
        camera->setScreenArea(gameOwner->getWindow()->getInnerSize());
    }
}

void Scene::onUpdate(float deltaTime)
{
    m_entitySystem->onUpdate(deltaTime);
}

void Scene::onFixedUpdate(float fixedDeltaTime)
{
    m_entitySystem->onFixedUpdate(fixedDeltaTime);
}

void Scene::onLateUpdate(float deltaTime)
{
    m_entitySystem->onLateUpdate(deltaTime);
}

void Scene::onResize(int _width, int _height)
{
    for (auto camera : m_entitySystem->getCameras())
    {
        camera->setScreenArea(Vector2(_width, _height));
    }
}

void Scene::onQuit()
{
    m_entitySystem->clearEntities();
}
