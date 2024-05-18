/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Texture2D.h
Description : Texture2D class is a representation of a 2D texture to be used by the graphics engine class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"

/**
 * @class Texture2D
 * @brief A representation of a 2D texture to be used by the graphics engine class.
 */
class Texture2D
{
public:
    /**
     * @brief Constructor for the Texture2D class.
     * @param desc Description of the 2D texture.
     */
    Texture2D(const Texture2DDesc& desc);

    /**
     * @brief Sets the texture wrapping mode to mirrored.
     */
    void setMirrored();

    /**
     * @brief Sets the texture wrapping mode to clamp to edge.
     */
    void setClampToEdge();

    /**
     * @brief Destructor for the Texture2D class.
     */
    ~Texture2D();

    /**
     * @brief Gets the ID of the texture.
     * @return The ID of the texture.
     */
    uint getId() const;

private:
    uint m_textureId = 0; //The ID of the texture.
    Texture2DDesc m_desc = {}; //Description of the 2D texture.
};