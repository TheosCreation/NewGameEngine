#pragma once
#include <map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"

class Texture : public Resource
{
public:
	Texture(const wchar_t* path, ResourceManager* manager);
	virtual ~Texture();

	Texture2DPtr getTexture2D();

private:
	Texture2DPtr m_texture2D;
};

