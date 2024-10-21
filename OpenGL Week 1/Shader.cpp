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
#include "Texture.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const ShaderDesc& desc)
{
	m_programId = glCreateProgram();
    Attach(desc.vertexShaderFileName, ShaderTypes::VertexShader);
    Attach(desc.fragmentShaderFileName, ShaderTypes::FragmentShader);
    //Attach(desc.tessellationControlFileName, ShaderTypes::TessellationControlShader);
    //Attach(desc.tessellationEvaluationFileName, ShaderTypes::TessellationEvaluationShader);
	link();
}

Shader::Shader(const string fileName, ShaderTypes _shaderType)
{
    m_programId = glCreateProgram();
    Attach(fileName, _shaderType);
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

void Shader::Attach(const std::string& filename, const ShaderTypes& type)
{
    std::string filePath;
    std::ifstream shaderStream;
    std::string shaderCode;

    // Set file path based on shader type
    switch (type)
    {
    case ShaderTypes::VertexShader:
        filePath = "Resources/Shaders/Vertex/" + filename + ".vert";
        break;
    case ShaderTypes::FragmentShader:
        filePath = "Resources/Shaders/Fragment/" + filename + ".frag";
        break;
    case ShaderTypes::ComputeShader:
        filePath = "Resources/Shaders/Compute/" + filename + ".comp";
        break;
    case ShaderTypes::TessellationControlShader:
        filePath = "Resources/Shaders/Tessellation/" + filename + ".tesc";
        break;
    case ShaderTypes::TessellationEvaluationShader:
        filePath = "Resources/Shaders/Tessellation/" + filename + ".tese";
        break;
    default:
        Debug::LogWarning("Shader | Cannot find file: " + filePath);
        return;
    }

    // Open the shader file
    shaderStream.open(filePath.c_str(), std::ios::in);
    if (!shaderStream.good()) {
        Debug::LogWarning("Shader | Cannot read file: " + filePath);
        shaderStream.close();
        return;
    }

    // Read the shader code into a string
    shaderStream.seekg(0, std::ios::end);
    shaderCode.resize(static_cast<size_t>(shaderStream.tellg()));
    shaderStream.seekg(0, std::ios::beg);
    shaderStream.read(&shaderCode[0], shaderCode.size());
    shaderStream.close();

    // Preprocess the shader code to handle includes
    shaderCode = PreprocessShader(shaderCode);

    // Determine shader type for OpenGL
    GLenum glShaderType;
    switch (type)
    {
    case ShaderTypes::VertexShader:
        glShaderType = GL_VERTEX_SHADER;
        break;
    case ShaderTypes::FragmentShader:
        glShaderType = GL_FRAGMENT_SHADER;
        break;
    case ShaderTypes::ComputeShader:
        glShaderType = GL_COMPUTE_SHADER;
        break;
    case ShaderTypes::TessellationControlShader:
        glShaderType = GL_TESS_CONTROL_SHADER;
        break;
    case ShaderTypes::TessellationEvaluationShader:
        glShaderType = GL_TESS_EVALUATION_SHADER;
        break;
    default:
        Debug::LogWarning("Shader | Unsupported shader type");
        return;
    }

    // Create and compile the shader
    uint shaderId = glCreateShader(glShaderType);
    const char* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, nullptr);
    glCompileShader(shaderId);

    // Check for compile errors
    int logLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        std::vector<char> errorMessage(logLength + 1);
        glGetShaderInfoLog(shaderId, logLength, nullptr, &errorMessage[0]);
        Debug::LogError("Shader | " + filePath + " compiled with errors: " + std::string(errorMessage.data()));
        return;
    }

    // Attach the shader to the program
    glAttachShader(m_programId, shaderId);
    m_attachedShaders[static_cast<uint>(type)] = shaderId;

    Debug::Log("Shader | " + filePath + " compiled successfully");
}

// Function to read shader code from a file
std::string Shader::ReadShaderFile(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;

    if (shaderFile.is_open()) {
        shaderStream << shaderFile.rdbuf();
    }
    else {
        Debug::LogWarning("Shader | Could not open file: " + filePath);
    }

    return shaderStream.str();
}

// Function to preprocess shader code
std::string Shader::PreprocessShader(const std::string& shaderCode) {
    std::string processedCode;
    std::istringstream stream(shaderCode);
    std::string line;

    while (std::getline(stream, line)) {
        // Check for #include directive
        if (line.find("#include") != std::string::npos) {
            // Extract the file path from the line
            std::string includeFilePath = line.substr(line.find('"') + 1);
            includeFilePath = includeFilePath.substr(0, includeFilePath.find('"'));

            // Read the included file
            std::string includedCode = ReadShaderFile("Resources/Shaders/" + includeFilePath);
            processedCode += includedCode + "\n"; // Add included code
        }
        else {
            processedCode += line + "\n"; // Add original line
        }
    }

    return processedCode;
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

void Shader::setTexture2D(const uint textureId, uint slot, std::string bindingName)
{
    auto glSlot = GL_TEXTURE0 + slot;
    glActiveTexture(glSlot); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    setInt(bindingName, slot);
}

void Shader::setTexture2D(const TexturePtr& texture, uint slot, std::string bindingName)
{
    auto glSlot = GL_TEXTURE0 + slot;
    glActiveTexture(glSlot); // activate the texture unit first before binding texture

    if (texture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        setInt(bindingName, slot);
    }
    else
    {
        //unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Shader::setTextureCubeMap(const TexturePtr& texture, uint slot, std::string bindingName)
{
    auto glSlot = GL_TEXTURE0 + slot;
    glActiveTexture(glSlot); // activate the texture unit first before binding/unbinding texture
    if (texture != nullptr)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture->getId());
        setInt(bindingName, slot);
    }
    else
    {
        //unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}