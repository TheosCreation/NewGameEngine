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