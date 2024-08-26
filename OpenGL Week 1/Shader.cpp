/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Shader.cpp
Description : Shader class is a wrapper class for handling shaders in OpenGL
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const ShaderDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFileName, ShaderType::VertexShader);
	attach(desc.fragmentShaderFileName, ShaderType::FragmentShader);
	link();
}

Shader::~Shader()
{
	for (uint i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programId);
}

void Shader::attach(string filename, const ShaderType& type)
{
	string filePath;
	// Open the file for reading
	std::ifstream shaderStream;
	string shaderCode;

	if (type == ShaderType::VertexShader)
	{
		filePath = "Resources/Shaders/Vertex/" + filename + ".vert";
	}
	else if (type == ShaderType::FragmentShader)
	{
		filePath = "Resources/Shaders/Fragment/" + filename + ".frag";
	}
	else
	{
		Debug::LogWarning("Shader | Cannot find file: " + filePath);

		return;
	}

	shaderStream.open(filePath.c_str(), std::ios::in);

	if (!shaderStream.good()) {
		Debug::LogWarning("Shader | Cannot read file: " + filePath);

		shaderStream.close();
		return;
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	shaderStream.seekg(0, std::ios::end);
	shaderCode.resize((uint)shaderStream.tellg());

	// Set the position of the next character to be read back to the beginning
	shaderStream.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	shaderStream.read(&shaderCode[0], shaderCode.size());
	shaderStream.close();

	// Attach shaders with unique ids to the program
	uint shaderId = 0;
	if (type == ShaderType::VertexShader)
	{
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == ShaderType::FragmentShader)
	{
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
	}
	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	glCompileShader(shaderId);

	//get compile errors
	int logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
		Debug::LogError("Shader | " + filePath + " compiled with errors: "  + errorMessage[0]);
		return;
	}

	glAttachShader(m_programId, shaderId);
	m_attachedShaders[(uint)type] = shaderId;

	Debug::Log("Shader | " + filePath + " compiled successfully");
}

void Shader::link()
{
	glLinkProgram(m_programId);

	//get compile errors
	int logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		Debug::LogWarning("Shader | " + errorMessage[0]);
		return;
	}
}

uint Shader::getId()
{
	return m_programId;
}