/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
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

class Texture : public Resource
{
public:
	Texture(const wchar_t* path, ResourceManager* manager);
	virtual ~Texture();

	Texture2DPtr getTexture2D() const;

private:
	Texture2DPtr m_texture2D;
};