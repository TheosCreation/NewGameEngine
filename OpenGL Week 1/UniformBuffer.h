#pragma once
#include "Prerequisites.h"

class UniformBuffer
{
public:
	UniformBuffer(const UniformBufferDesc& desc);
	~UniformBuffer();

	void setData(void* data);

	uint getId();
private:
	uint m_id = 0;
	uint m_size = 0;
};

