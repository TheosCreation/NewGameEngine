#include "Scene.h"

Scene::Scene(Game* game)
{
    gameOwner = game;
}

Scene::~Scene()
{
}

void Scene::onGraphicsUpdate(float deltaTime)
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

    m_entitySystem->onGraphicsUpdate(deltaTime, data);

   //graphicsEngine.setStencil(StencilOperationType::Set);
   //graphicsEngine.setStencil(StencilOperationType::ResetAlways);
   //
   //m_entitySystem->onGraphicsUpdate(deltaTime, data);
   //
   //graphicsEngine.setStencil(StencilOperationType::ResetNotEqual);
   //
   //for (auto& graphicEntity : m_entitySystem->getGraphicsEntities())
   //{
   //    Vector3 originalScale = graphicEntity->getScale();
   //    graphicEntity->setScale(Vector3(originalScale * 1.1f));
   //    graphicEntity->setColor(Color::Red);
   //    ShaderPtr originalShader = graphicEntity->getShader();
   //    graphicEntity->setShader(m_solidColorMeshShader);
   //    graphicEntity->onGraphicsUpdate(data);
   //    graphicEntity->setScale(originalScale);
   //    graphicEntity->setShader(originalShader);
   //}
   ////m_entitySystem->onGraphicsUpdate(deltaTime, data);
   //
   //glDisable(GL_STENCIL_TEST);
   //graphicsEngine.setStencil(StencilOperationType::ResetAlways);
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

    m_skyBox->setEntitySystem(m_entitySystem.get());
    m_skyBox->setMesh(gameOwner->getCubeMesh());
    m_skyBox->setShader(skyboxShader);

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

void Scene::onQuit()
{
    m_entitySystem->clearEntities();
}
