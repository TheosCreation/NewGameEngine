#include "Texture.h"
#include "ResourceManager.h"
#include "Game.h"
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const wchar_t* path, ResourceManager* manager):Resource(path, manager)
{
	Rect textureSize;
	auto nrChannels = 0;

	std::filesystem::path resPath = path;
	auto str = resPath.generic_string();

	unsigned char* data = stbi_load(str.c_str(), &textureSize.width, &textureSize.height, &nrChannels, 0);

	if (data)
	{
		m_texture2D = manager->getGame()->getGraphicsEngine()->createTexture2D({ data,textureSize, (uint)nrChannels });
		if (!m_texture2D) OGL3D_ERROR("Texture not generated");
	}
	else
	{
		OGL3D_ERROR("Texture not generated");
	}

	stbi_image_free(data);
}

Texture::~Texture()
{
}

Texture2DPtr Texture::getTexture2D()
{
	return m_texture2D;
}
