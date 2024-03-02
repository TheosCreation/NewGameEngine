#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <glew.h>

class VertexArrayObject;
class UniformBuffer;
class ShaderProgram;

typedef unsigned int uint;
typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

struct VertexAttribute
{
	uint numElements = 0;
};

struct VertexBufferDesc
{
	void* verticesList = nullptr;
	uint vertexSize = 0;
	uint listSize = 0;

	VertexAttribute* attributesList = nullptr;
	uint attributesListSize = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFileName;
	const wchar_t* fragmentShaderFileName;
};

struct UniformBufferDesc
{
	uint size = 0;
};

enum TriangleType
{
	TriangleList = 0,
	TriangleStrip
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader
};

#define OGL3D_ERROR(message)\
{\
	std::stringstream m;\
	m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;
