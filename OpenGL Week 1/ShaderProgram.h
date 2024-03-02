#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Prerequisites.h"

class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();
	uint getId();
	void setUniformBufferSlot(const char* name, uint slot);
private:
	void attach(const wchar_t* filename, const ShaderType& type);
	void link();
private:
	uint m_programId = 0;
	uint m_attachedShaders[2] = {};
};

