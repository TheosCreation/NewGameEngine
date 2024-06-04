/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : ResourceManager.h
Description : ResourceManager class manages the resources created with the resource class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <map>
#include <string>
#include "Utils.h"

// Forward declaration of Game class
class Game;

/**
 * @class ResourceManager
 * @brief Manages the resources created with the Resource class.
 */
class ResourceManager
{
public:
    /**
     * @brief Constructor for the ResourceManager class.
     * @param game Pointer to the game instance.
     */
    ResourceManager(Game* game);

    /**
     * @brief Destructor for the ResourceManager class.
     */
    virtual ~ResourceManager();

    /**
     * @brief Creates a resource from a file.
     * @param path The file path to the resource.
     * @return A shared pointer to the created resource.
     */
    ResourcePtr createResourceFromFile(const char* path);

    TextureCubeMapPtr createCubeMapTextureFromFile(const std::vector<std::string>& filepaths);

    Texture2DPtr createTexture2DFromFile(const std::string& filepath);

    MeshPtr createMeshFromFile(const std::string& filepath);

    InstancedMeshPtr createInstancedMeshFromFile(const std::string& filepath);

    /**
     * @brief Gets the game instance.
     * @return A pointer to the game instance.
     */
    Game* getGame();

protected:
    std::map<std::string, ResourcePtr> m_mapResources; //Map of resources keyed by their file paths
    Game* m_game = nullptr; //Pointer to the game instance
};