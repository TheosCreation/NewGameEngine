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
#include <glm.hpp>
#include "Utils.h"

class Shader
{
public:
	Shader(const ShaderDesc& desc);
	~Shader();

	//returns id of the shader
	uint getId();

	// sends a mat4 into the shader
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	// sends a mat4 array into the shader
	void setMat4Array(const std::string& name, const glm::mat4 mat[], int count) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), count, GL_FALSE, &mat[0][0][0]);
	}

	// sends a float into the shader
	void setFloat(const std::string& name, const float value) const
	{
		glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
	}

	// sends a vec3 into the shader
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

