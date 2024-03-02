#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Prerequisites.h"

class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();
	unsigned int getId();
private:
	void attach(const wchar_t* filename, const ShaderType& type);
	void link();
private:
	unsigned int m_programId = 0;
	unsigned int m_attachedShaders[2] = {};
};

