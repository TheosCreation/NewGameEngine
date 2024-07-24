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
     * @brief Creates a cube map texture from file paths.
     * @param filepaths A vector of file paths for the cube map textures.
     * @return A shared pointer to the created cube map texture.
     */
    TextureCubeMapPtr createCubeMapTextureFromFile(const std::vector<std::string>& filepaths);

    /**
     * @brief Creates a 2D texture from a file path.
     * @param filepath The file path for the 2D texture.
     * @return A shared pointer to the created 2D texture.
     */
    Texture2DPtr createTexture2DFromFile(const std::string& filepath, TextureType type = TextureType::Default);
    
    /**
     * @brief Creates a mesh from a file path.
     * @param filepath The file path for the mesh.
     * @return A shared pointer to the created mesh.
     */
    MeshPtr createMeshFromFile(const std::string& filepath);

    /**
     * @brief Creates an instanced mesh from a file path.
     * @param filepath The file path for the instanced mesh.
     * @return A shared pointer to the created instanced mesh.
     */
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