/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Texture.cpp
Description : Texture class is a resource that represents a texture used by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Constructor that initializes a texture from a file path and a resource manager.
Texture::Texture(const char* path, ResourceManager* manager) : Resource(path, manager)
{
    Rect textureSize; // Structure to hold the texture size.
    auto nrChannels = 0; // Number of color channels in the texture.

    // Load the image data using stb_image.
    unsigned char* data = stbi_load(path, &textureSize.width, &textureSize.height, &nrChannels, 0);

    if (data)
    {
        // Create a 2D texture using the graphics engine.
        m_texture2D = manager->getGame()->getGraphicsEngine()->createTexture2D({ data, textureSize, (uint)nrChannels });
        if (!m_texture2D)
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
}

// Constructor that initializes a cubemap texture from an array of file paths and a resource manager.
Texture::Texture(const std::vector<std::string>& paths, ResourceManager* manager) : Resource("", manager)
{
    if (paths.size() != 6)
    {
        OGL3D_ERROR("Cubemap texture requires exactly 6 images");
        return;
    }

    TextureCubeMapDesc desc;
    for (const auto& path : paths)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            desc.textureData.push_back(data);
            desc.textureSize = { width, height };
            desc.numChannels = nrChannels;
        }
        else
        {
            OGL3D_ERROR("Cubemap texture failed to load at path: " + path);
            stbi_image_free(data);
            return;
        }
    }

    // Create a cubemap texture using the graphics engine.
    m_textureCubeMap = manager->getGame()->getGraphicsEngine()->createTextureCubeMap(desc);
    if (!m_textureCubeMap)
    {
        OGL3D_ERROR("Cubemap texture not generated");
    }

    // Free the image data.
    for (auto data : desc.textureData)
    {
        stbi_image_free(data);
    }
}

// Destructor for the Texture class.
Texture::~Texture()
{
}

// Returns the 2D texture pointer.
Texture2DPtr Texture::getTexture2D() const
{
    return m_texture2D;
}

// Returns the cubemap texture pointer.
TextureCubeMapPtr Texture::getTextureCubeMap() const
{
    return m_textureCubeMap;
}