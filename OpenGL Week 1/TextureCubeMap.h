/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : TextureCubeMap.h
Description : TextureCubeMap class is a resource that represents a cubemap texture used by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"

/**
 * @class TextureCubeMap
 * @brief A resource that represents a cubemap texture used by the graphics engine.
 */
class TextureCubeMap
{
public:
    /**
     * @brief Constructor for the TextureCubeMap class.
     * @param faces The file paths to the six faces of the cubemap.
     * @param manager Pointer to the resource manager.
     */
    TextureCubeMap(const TextureCubeMapDesc& desc);

    /**
     * @brief Destructor for the TextureCubeMap class.
     */
    ~TextureCubeMap();

    /**
     * @brief Gets the ID of the texture.
     * @return The ID of the texture.
     */
    uint getId() const;

private:
    uint m_textureId = 0; //The ID of the texture.
    TextureCubeMapDesc m_desc = {}; //Description of the 2D texture.
};