#pragma once
#include "Utils.h"
#include "All.h"

class Game;

class Scene
{
public:
	Scene(Game* game);
	~Scene();

	virtual void onShadowPass();
	virtual void onGeometryPass();
	virtual void onLightingPass();

    /**
     * @brief Default rendering mode is deffered rendering
     */
	virtual void onGraphicsUpdate();


    /**
     * @brief Called when the game is created.
     */
    virtual void onCreate();

    /**
     * @brief Called when the game is created and after onCreate.
     */
    virtual void onCreateLate();

    /**
     * @brief Called every frame to update the game logic.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onUpdate(float deltaTime);

    /**
     * @brief Called every frame to update the entity at a fixed frame rate.
     * Can be overridden by derived classes to implement custom behavior.
     */
    virtual void onFixedUpdate(float fixedDeltaTime);

    /**
     * @brief Called every frame to post graphics update/render.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onLateUpdate(float deltaTime);
    virtual void onResize(int _width, int _height);

    /**
     * @brief Called when the game is quitting.
     */
    virtual void onQuit();

protected:
    ShaderPtr m_solidColorMeshShader = nullptr;
    ShaderPtr m_shadowShader = nullptr;
    ShaderPtr m_shadowInstancedShader = nullptr;
    ShaderPtr m_meshGeometryShader = nullptr;
    //ShaderPtr m_meshLightingShader = nullptr;
    ShaderPtr m_skyboxGeometryShader = nullptr;
    ShaderPtr m_instancedmeshGeometryShader = nullptr;
    ShaderPtr m_terrainGeometryShader = nullptr;
    unique_ptr<SkyboxEntity> m_skyBox; //Pointer to the sky box instance
    unique_ptr<EntitySystem> m_entitySystem; //Pointer to the entity system instance
    FramebufferPtr m_postProcessingFramebuffer; //Pointer to the framebuffer instance
    Game* gameOwner;
    vector<MeshEntity*> m_lights; //Pointers to the lights objects in the scene (point and spotlights)
};

