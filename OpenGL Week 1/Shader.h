/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Shader.h
Description : Shader class is a wrapper class for handling shaders in OpenGL
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Utils.h"
#include <glm.hpp>

class Shader
{
public:
	Shader(const ShaderDesc& desc);
	~Shader();
	uint getId();
	void setUniformBufferSlot(const char* name, uint slot);

	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	
	void setMat4Array(const std::string& name, const glm::mat4 mat[], int count) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), count, GL_FALSE, &mat[0][0][0]);
	}
	
	void setFloat(const std::string& name, const float value) const
	{
		glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
	}
	
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
	}
private:
	void attach(const wchar_t* filename, const ShaderType& type);
	void link();
private:
	uint m_programId = 0;
	uint m_attachedShaders[2] = {};
};

