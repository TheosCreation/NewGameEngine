#include "ShaderProgram.h"
#include<iostream>
#include<fstream>
#include<sstream>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();
	attach(desc.vertexShaderFileName, VertexShader);
	attach(desc.fragmentShaderFileName, FragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	for (unsigned int i = 0; i < 2; i++)
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
		std::cout << "Invalid shader type for file: " << filename << std::endl;
		return;
	}

	shaderStream.open(filePath.c_str(), std::ios::in);

	if (!shaderStream.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;

		shaderStream.close();
		return;
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	shaderStream.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)shaderStream.tellg());

	// Set the position of the next character to be read back to the beginning
	shaderStream.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	shaderStream.read(&shaderCode[0], shaderCode.size());
	shaderStream.close();

	// Attach shaders with unique ids to the program
	unsigned int shaderId = 0;
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

	glAttachShader(m_programId, shaderId);
	m_attachedShaders[type] = shaderId;
}

void ShaderProgram::link()
{
	glLinkProgram(m_programId);
}

unsigned int ShaderProgram::getId()
{
	return m_programId;
}
