/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Shader.h
Description : Shader class is a wrapper class for handling shaders in OpenGL
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <glew.h>
#include <glm.hpp>
#include "Utils.h"

/**
 * @class Shader
 * @brief A wrapper class for handling shaders in OpenGL.
 */
class Shader
{
public:
	/**
     * @brief Constructor for the Shader class.
     * @param desc A description of the shader.
     */
	Shader(const ShaderDesc& desc);

	/**
	 * @brief Destructor for the Shader class.
	 */
	~Shader();

	/**
	* @brief Gets the ID of the shader program.
	* @return The ID of the shader program.
	*/
	uint getId();

	/**
	 * @brief Sends a mat4 into the shader.
	 * @param name The name of the uniform variable in the shader.
	 * @param mat The mat4 value to send.
	 */
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	/**
	 * @brief Sends a mat4 array into the shader.
	 * @param name The name of the uniform variable in the shader.
	 * @param mat The array of mat4 values to send.
	 * @param count The number of mat4 values in the array.
	 */
	void setMat4Array(const std::string& name, const glm::mat4 mat[], int count) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), count, GL_FALSE, &mat[0][0][0]);
	}

	/**
	 * @brief Sends a float into the shader.
	 * @param name The name of the uniform variable in the shader.
	 * @param value The float value to send.
	 */
	void setFloat(const std::string& name, const float value) const
	{
		glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
	}

	/**
	 * @brief Sends a vec3 into the shader.
	 * @param name The name of the uniform variable in the shader.
	 * @param value The vec3 value to send.
	 */
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
	}
	
	void setUint(const std::string& name, const uint value) const
	{
		glUniform1ui(glGetUniformLocation(m_programId, name.c_str()), value);
	}

private:
	/**
     * @brief Attaches a shader to the program.
     * @param filename The filename of the shader source.
     * @param type The type of the shader (vertex, fragment, etc.).
     */
	void attach(const wchar_t* filename, const ShaderType& type);

	/**
	 * @brief Links the shader program.
	 */
	void link();
private:
	uint m_programId = 0; //The ID of the shader program.
	uint m_attachedShaders[2] = {};  //The IDs of the attached shaders.
};

