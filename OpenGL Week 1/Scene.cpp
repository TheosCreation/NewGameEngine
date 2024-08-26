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

    //graphicsEngine.setScissor(true);
    //m_graphicsEngine->setStencil(StencilOperationType::Set);
    //m_graphicsEngine->setStencil(StencilOperationType::ResetAlways);

    //for (auto& graphicsEntity : m_entitySystem->getGraphicsEntities())
    //{
    //    ShaderPtr shader = graphicsEntity->getShader();
    //    graphicsEngine.setShader(shader);

    //    // Apply other uniform data to the shader
    //    graphicsEntity->setUniformData(data);

    //    graphicsEntity->onGraphicsUpdate(deltaTime);
    //}

    m_entitySystem->onGraphicsUpdate(deltaTime, data);
    
    //graphicsEngine.setScissor(false);
    //m_graphicsEngine->setStencil(StencilOperationType::ResetNotEqual);
    //
    //for (auto& [key, entities] : m_entitySystem->m_entities)
    //{
    //    // For each graphics entity
    //    for (auto& [key, entity] : entities)
    //    {
    //        auto e = dynamic_cast<GraphicsEntity*>(entity.get());
    //        if (e)
    //        {
    //            ShaderPtr shader = e->getShader();
    //            if (shader != currentShader)
    //            {
    //                // Set the shader only if it is different from the current one
    //                m_graphicsEngine->setShader(shader);
    //                // Apply lighting to the shader
    //                m_lightManager->applyLighting(shader);
    //                currentShader = shader;
    //            }
    //
    //            // Apply other uniform data to the shader
    //            e->setUniformData(data);
    //            e->onGraphicsUpdate(deltaTime);
    //        }
    //        else
    //        {
    //            break;
    //        }
    //    }
    //}
    //m_graphicsEngine->setStencil(StencilOperationType::ResetAlways);

    //graphicsEngine.setScissor(false);
}

void Scene::onCreate()
{
    auto& resourceManager = ResourceManager::GetInstance();
    m_entitySystem = std::make_unique<EntitySystem>(this);

    //Creating skybox object
    m_skyBox = std::make_unique<SkyboxEntity>();
    ShaderPtr skyboxShader = GraphicsEngine::GetInstance().createShader({
            "SkyBoxShader",
            "SkyBoxShader"
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
