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

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* path)
{
    return createResourceFromFile(path, false);
}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* path, bool isInstanced)
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

    auto ext = resPath.extension();

    // If the resource has one of these extensions
    if (!ext.compare(L".jpg") || !ext.compare(L".png") || !ext.compare(L".bmp") || !ext.compare(L".tga"))
    {
        // Let's create a texture resource
        TexturePtr texturePtr = std::make_shared<Texture>(resPath.c_str(), this);
        if (texturePtr)
        {
            m_mapResources.emplace(path, texturePtr);
            return texturePtr;
        }
    }
    else if (!ext.compare(L".obj"))
    {
        if (isInstanced)
        {
            InstancedMeshPtr instancedMeshPtr = std::make_shared<InstancedMesh>(resPath.c_str(), this);
            if (instancedMeshPtr)
            {
                m_mapResources.emplace(path, instancedMeshPtr);
                return instancedMeshPtr;
            }
        }
        else
        {
            MeshPtr meshPtr = std::make_shared<Mesh>(resPath.c_str(), this);
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
