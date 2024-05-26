/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Texture.h
Description : Texture class is a resource that represents a texture used by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <map>
#include <string>
#include "Utils.h"
#include "Resource.h"

/**
 * @class Texture
 * @brief A resource that represents a texture used by the graphics engine.
 */
class Texture : public Resource
{
public:
    /**
     * @brief Constructor for the Texture class.
     * @param path The file path to the texture resource.
     * @param manager Pointer to the resource manager.
     */
    Texture(const char* path, ResourceManager* manager);

    Texture(const std::vector<std::string>& paths, ResourceManager* manager);

    /**
     * @brief Destructor for the Texture class.
     */
    virtual ~Texture();

    /**
     * @brief Gets the 2D texture.
     * @return A shared pointer to the 2D texture.
     */
    Texture2DPtr getTexture2D() const;

    TextureCubeMapPtr getTextureCubeMap() const;

private:
    Texture2DPtr m_texture2D; //A shared pointer to the 2D texture.
    TextureCubeMapPtr m_textureCubeMap; // A shared pointer to the cubemap texture.
};