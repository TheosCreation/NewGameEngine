#pragma once
#include "Prerequisites.h"

class Texture2D
{
public:
	Texture2D(const Texture2DDesc& desc);
	~Texture2D();
	uint getId();
private:
	uint m_textureId = 0;
	Texture2DDesc m_desc = {};
};

