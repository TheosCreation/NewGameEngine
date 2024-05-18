/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : ResourceManager.cpp
Description : ResourceManager class manages the resources created with the resource class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "ResourceManager.h"
#include "Texture.h"
#include "InstancedMesh.h"
#include "Mesh.h"
#include <filesystem>

ResourceManager::ResourceManager(Game* game)
{
	m_game = game;
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::createResourceFromFile(const char* path)
{
    return createResourceFromFile(path, false);
}

ResourcePtr ResourceManager::createResourceFromFile(const char* path, bool isInstanced)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(path);
    if (it != m_mapResources.end())
    {
        return it->second;
    }

    // The resource has not been loaded yet. Let's load it.
    std::filesystem::path resPath = path;
    if (!std::filesystem::exists(resPath)) return ResourcePtr();

    auto ext = resPath.extension(); // Pull the file extension

    // If the resource has one of these extensions
    if (ext == ".jpg" || ext == ".png" || ext == ".bmp" || ext == ".tga")
    {
        // Let's create a texture resource
        TexturePtr texturePtr = std::make_shared<Texture>(path, this);
        if (texturePtr)
        {
            m_mapResources.emplace(path, texturePtr);
            return texturePtr;
        }
    }
    else if (ext == ".obj")
    {
        if (isInstanced)
        {
            InstancedMeshPtr instancedMeshPtr = std::make_shared<InstancedMesh>(path, this);
            if (instancedMeshPtr)
            {
                m_mapResources.emplace(path, instancedMeshPtr);
                return instancedMeshPtr;
            }
        }
        else
        {
            MeshPtr meshPtr = std::make_shared<Mesh>(path, this);
            if (meshPtr)
            {
                m_mapResources.emplace(path, meshPtr);
                return meshPtr;
            }
        }
    }

    return ResourcePtr();
}

Game* ResourceManager::getGame()
{
    return m_game;
}
