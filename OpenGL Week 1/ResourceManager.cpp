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
#include "HeightMap.h"
#include "Mesh.h"
#include "Game.h"
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
TextureCubeMapPtr ResourceManager::createCubeMapTextureFromFile(const std::vector<std::string>& filepaths)
{

    stbi_set_flip_vertically_on_load(false);

    if (filepaths.size() != 6)
    {
        OGL3D_ERROR("Cubemap texture requires exactly 6 images");
        return TextureCubeMapPtr();
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
            return TextureCubeMapPtr();
        }
    }

    // Create a cubemap texture using the graphics engine.
    TextureCubeMapPtr textureCubeMapPtr = std::make_shared<TextureCubeMap>(desc, filepaths[0].c_str(), this);
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
        m_textureCubeMap = textureCubeMapPtr;
        return textureCubeMapPtr;
    }

    return TextureCubeMapPtr();
}

TexturePtr ResourceManager::createTextureFromId(const uint id)
{
    TexturePtr texturePtr = std::make_shared<Texture>(id, this);
    return texturePtr;
}

Texture2DPtr ResourceManager::createTexture2DFromFile(const std::string& filepath, TextureType type)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return std::static_pointer_cast<Texture2D>(it->second);
    }
    stbi_set_flip_vertically_on_load(false);

    // Load the image data using stb_image.
    Texture2DDesc desc;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (!data)
    {
        OGL3D_ERROR("Texture failed to load at path: " + filepath);
        return Texture2DPtr();
    }

    desc.textureData = data;
    desc.textureSize = { width, height };
    desc.numChannels = nrChannels;

    // Create a 2D texture using the graphics engine.
    Texture2DPtr texture2DPtr = std::make_shared<Texture2D>(desc, filepath.c_str(), this);
    if (!texture2DPtr)
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

    return Texture2DPtr();
}

MeshPtr ResourceManager::createMeshFromFile(const std::string& filepath)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return std::static_pointer_cast<Mesh>(it->second);
    }

    MeshPtr meshPtr = std::make_shared<Mesh>(filepath.c_str(), this);
    if (meshPtr)
    {
        m_mapResources.emplace(filepath, meshPtr);
        return meshPtr;
    }
    return MeshPtr();
}

InstancedMeshPtr ResourceManager::createInstancedMeshFromFile(const std::string& filepath)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return std::static_pointer_cast<InstancedMesh>(it->second);
    }

    InstancedMeshPtr instancedMeshPtr = std::make_shared<InstancedMesh>(filepath.c_str(), this);
    if (instancedMeshPtr)
    {
        m_mapResources.emplace(filepath, instancedMeshPtr);
        return instancedMeshPtr;
    }

    return InstancedMeshPtr();
}

HeightMapPtr ResourceManager::createHeightMapFromFile(const std::string& filepath)
{
    // Check if the resource has already been loaded
    auto it = m_mapResources.find(filepath);
    if (it != m_mapResources.end())
    {
        return std::static_pointer_cast<HeightMap>(it->second);
    }
    stbi_set_flip_vertically_on_load(false);

    // Load the image data using stb_image with original channels
    HeightMapDesc desc;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0); // Load with original channels
    if (!data)
    {
        OGL3D_ERROR("Heightmap failed to load at path: " + filepath);
        return HeightMapPtr();
    }

    if (nrChannels != 1)
    {
        // Manually convert the image to grayscale
        unsigned char* grayData = new unsigned char[width * height];
        for (int i = 0; i < width * height; ++i)
        {
            int r = data[i * nrChannels];
            int g = data[i * nrChannels + 1];
            int b = data[i * nrChannels + 2];
            grayData[i] = static_cast<unsigned char>(0.3f * r + 0.59f * g + 0.11f * b); // Convert RGB to grayscale
        }
        stbi_image_free(data); // Free the original RGB data
        data = grayData; // Use the grayscale data
        nrChannels = 1; // Update the channel count
        OGL3D_WARNING("Heightmap texture converted to grayscale texture at path: " << filepath.c_str());
    }

    // Process heightmap data if needed (e.g., normalize values)
    for (int i = 0; i < width * height; ++i)
    {
        data[i] = static_cast<unsigned char>(data[i] / 255.0f * 1.0f); // Example normalization to 0.0 - 1.0 range
    }

    desc.textureData = data;
    desc.textureSize = { width, height };
    desc.numChannels = nrChannels;

    // Create a HeightMap using the graphics engine.
    HeightMapPtr heightMapPtr = std::make_shared<HeightMap>(desc, filepath.c_str(), this);
    if (!heightMapPtr)
    {
        OGL3D_ERROR("Heightmap not generated");
    }

    // Free the grayscale image data.
    stbi_image_free(data);

    if (heightMapPtr)
    {
        m_mapResources.emplace(filepath, heightMapPtr);
        return heightMapPtr;
    }

    return HeightMapPtr();
}

TexturePtr ResourceManager::getSkyboxTexture()
{
    return m_textureCubeMap;
}

void ResourceManager::ClearInstancesFromMeshes()
{
    // Iterate over all resources in the map
    for (auto& [key, resource] : m_mapResources)
    {
        // Check if the resource is of type InstancedMesh
        InstancedMeshPtr instancedMeshPtr = std::dynamic_pointer_cast<InstancedMesh>(resource);
        if (instancedMeshPtr)
        {
            instancedMeshPtr->clearInstances();
        }
    }
}