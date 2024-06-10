/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Texture.cpp
Description : Texture class handles the loading and management of texture resources.
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Texture.h"

Texture::Texture(const char* path, ResourceManager* manager) : Resource(path, manager)
{
}

Texture::~Texture()
{
}

// Returns the OpenGL texture ID.
uint Texture::getId() const
{
    return m_textureId;
}