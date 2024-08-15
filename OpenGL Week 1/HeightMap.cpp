#include "HeightMap.h"
#include <glew.h>

HeightMap::HeightMap(const HeightMapDesc& desc, const char* path, ResourceManager* manager) : Texture(path, manager)
{
    // Generate a texture ID and bind it as a 2D texture.
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    // Set texture wrapping parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat texture horizontally.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat texture vertically.

    // Set texture filtering parameters.
    if (desc.generateMipmaps)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Use linear filtering and generate mipmaps.
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use linear filtering without mipmaps.
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use linear filtering for magnification.

    // Determine the correct format for the height map.
    auto glChannels = GL_RED; // Typically, height maps use a single channel (red).
    if (desc.numChannels == 1) glChannels = GL_RED; // 1 channel (Grayscale).
    else if (desc.numChannels == 3) glChannels = GL_RGB; // 3 channels (RGB) - if needed.
    else if (desc.numChannels == 4) glChannels = GL_RGBA; // 4 channels (RGBA) - if needed.

    // Specify the 2D texture image.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, desc.textureSize.width, desc.textureSize.height, 0, glChannels, GL_UNSIGNED_BYTE, desc.textureData);

    // Generate mipmaps for the texture if specified.
    if (desc.generateMipmaps)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Store the texture description.
    m_desc = desc;
}


float HeightMap::getHeight()
{
    return m_desc.textureSize.height;
}

float HeightMap::getWidth()
{
    return m_desc.textureSize.width;
}

unsigned char* HeightMap::getData() const
{
    if (!m_desc.textureData)
    {
        OGL3D_ERROR("Texture data is null");
    }
    return m_desc.textureData;
}

HeightMap::~HeightMap()
{
}
