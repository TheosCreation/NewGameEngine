/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Texture2D.h
Description : Texture2D class is a representation of a 2D texture to be used by the graphics engine class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"

class Texture2D
{
public:
	Texture2D(const Texture2DDesc& desc);
	void setMirrored();
	void setClampToEdge();
	~Texture2D();
	uint getId();
private:
	uint m_textureId = 0;
	Texture2DDesc m_desc = {};
};

