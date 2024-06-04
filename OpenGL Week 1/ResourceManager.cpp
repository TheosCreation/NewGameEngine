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
#include "InstancedMesh.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"
#include "Mesh.h"
#include "Game.h"
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

TextureCubeMapPtr ResourceManager::createCubeMapTextureFromFile(const std::vector<std::string>& filepaths)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepaths[1]);
    if (it != m_mapResources.end())
    {
        return it->second;
    }

    stbi_set_flip_vertically_on_load(false);

    if (filepaths.size() != 6)
    {
        OGL3D_ERROR("Cubemap texture requires exactly 6 images");
        return;
    }

    TextureCubeMapDesc desc;
    for (const auto& filepath : filepaths)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            desc.textureData.push_back(data);
            desc.textureSize = { width, height };
            desc.numChannels = nrChannels;
        }
        else
        {
            OGL3D_ERROR("Cubemap texture failed to load at path: " + filepath);
            stbi_image_free(data);
            return;
        }
    }

    // Create a cubemap texture using the graphics engine.
    TextureCubeMapPtr textureCubeMapPtr = getGame()->getGraphicsEngine()->createTextureCubeMap(desc);
    if (!textureCubeMapPtr)
    {
        OGL3D_ERROR("Cubemap texture not generated");
    }

    // Free the image data.
    for (auto data : desc.textureData)
    {
        stbi_image_free(data);
    }

    if (textureCubeMapPtr)
    {
        m_mapResources.emplace(filepaths[1], textureCubeMapPtr);
        return textureCubeMapPtr;
    }

    return TextureCubeMapPtr();
}

ResourcePtr ResourceManager::createTexture2DFromFile(const std::string& filepath)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return it->second;
    }
    stbi_set_flip_vertically_on_load(false);

    Rect textureSize; // Structure to hold the texture size.
    auto nrChannels = 0; // Number of color channels in the texture.

    // Load the image data using stb_image.
    unsigned char* data = stbi_load(filepath.c_str(), &textureSize.width, &textureSize.height, &nrChannels, 0);
    Texture2DPtr texture2DPtr;
    if (data)
    {
        // Create a 2D texture using the graphics engine.
        texture2DPtr = getGame()->getGraphicsEngine()->createTexture2D({ data, textureSize, (uint)nrChannels });
        if (!texture2DPtr)
        {
            OGL3D_ERROR("Texture not generated");
        }
    }
    else
    {
        OGL3D_ERROR("Texture not generated");
    }

    // Free the image data.
    stbi_image_free(data);

    if (texture2DPtr)
    {
        m_mapResources.emplace(filepath, texture2DPtr);
        return texture2DPtr;
    }

    return ResourcePtr();
}

ResourcePtr ResourceManager::createMeshFromFile(const std::string& filepath)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return it->second;
    }

    MeshPtr meshPtr = std::make_shared<Mesh>(filepath, this);
    if (meshPtr)
    {
        m_mapResources.emplace(filepath, meshPtr);
        return meshPtr;
    }
    return ResourcePtr();
}

ResourcePtr ResourceManager::createInstancedMeshFromFile(const std::string& filepath)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return it->second;
    }

    InstancedMeshPtr instancedMeshPtr = std::make_shared<InstancedMesh>(filepath, this);
    if (instancedMeshPtr)
    {
        m_mapResources.emplace(filepath, instancedMeshPtr);
        return instancedMeshPtr;
    }

    return ResourcePtr();
}

Game* ResourceManager::getGame()
{
    return m_game;
}
