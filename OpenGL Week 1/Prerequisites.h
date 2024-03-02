#pragma once
#include <memory>

class VertexArrayObject;
class ShaderProgram;

typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

struct VertexAttribute
{
	unsigned int numElements = 0;
};

struct VertexBufferDesc
{
	void* verticesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;

	VertexAttribute* attributesList = nullptr;
	unsigned int attributesListSize = 0;
};

struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFileName;
	const wchar_t* fragmentShaderFileName;
};

enum ShaderType
{
	VertexShader = 0,
	FragmentShader
};
