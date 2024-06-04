#pragma once
#include "Resource.h"

class Texture : public Resource
{
public:
	Texture(const char* path, ResourceManager* manager);
	~Texture();

    /**
     * @brief Gets the ID of the texture.
     * @return The ID of the texture.
     */
    uint getId() const;

protected:
    uint m_textureId = 0;
};

