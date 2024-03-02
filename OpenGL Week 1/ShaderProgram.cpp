#include "ShaderProgram.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include <vector>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFileName, VertexShader);
	attach(desc.fragmentShaderFileName, FragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	for (uint i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programId);
}

void ShaderProgram::attach(const wchar_t* filename, const ShaderType& type)
{
	// for file reading
	std::wstring wstr(filename);
	std::wstring filePath;

	// Open the file for reading
	std::ifstream shaderStream;
	std::string shaderCode;

	if (type == VertexShader)
	{
		filePath = L"Resources/Shaders/" + wstr + L".vert";
	}
	else if (type == FragmentShader)
	{
		filePath = L"Resources/Shaders/" + wstr + L".frag";
	}
	else
	{
		OGL3D_WARNING("ShaderProgram | Cannot find file: " << filename << std::endl);

		return;
	}

	shaderStream.open(filePath.c_str(), std::ios::in);

	if (!shaderStream.good()) {
		OGL3D_WARNING("ShaderProgram | Cannot read file: " << filename << std::endl);

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
	if (type == VertexShader)
	{
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == FragmentShader)
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
		OGL3D_WARNING("ShaderProgram | " << filename << " compiled with errors:" << std::endl << &errorMessage[0]);
		return;
	}

	glAttachShader(m_programId, shaderId);
	m_attachedShaders[type] = shaderId;

	OGL3D_INFO("ShaderProgram | " << filename << " compiled successfully");
}

void ShaderProgram::link()
{
	glLinkProgram(m_programId);

	//get compile errors
	int logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("ShaderProgram | " << &errorMessage[0]);
		return;
	}
}

uint ShaderProgram::getId()
{
	return m_programId;
}

void ShaderProgram::setUniformBufferSlot(const char* name, uint slot)
{
	uint index = glGetUniformBlockIndex(m_programId, name);
	glUniformBlockBinding(m_programId, index, slot);
}
