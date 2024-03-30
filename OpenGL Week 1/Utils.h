#pragma once
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <glm.hpp>
#include "Rect.h"

class UniformBuffer;
class VertexArrayObject;
class ShaderProgram;
class Texture2D;

class ResourceManager;
class Resource;
class Texture;

typedef unsigned int uint;
typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;

typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;

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

struct IndexBufferDesc
{
	void* indicesList = nullptr;
	uint listSize = 0;
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

struct UniformData
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	float currentTime;
	glm::vec3 color;
};

struct Texture2DDesc
{
	void* textureData = nullptr;
	Rect textureSize = {};
	uint numChannels = 0;
};

enum class CameraType
{
	Orthogonal = 0,
	Perspective
};

enum class TriangleType
{
	TriangleList = 0,
	TriangleStrip
}; 

enum class CullType
{
	BackFace = 0,
	FrontFace,
	Both,
	None
};

enum class WindingOrder
{
	ClockWise = 0,
	CounterClockWise
};

enum class ShaderType
{
	VertexShader = 0,
	FragmentShader
};

enum Key
{
	KeyEscape = 0,
	KeyShift,
	KeyA,
	KeyB,
	KeyC,
	KeyD,
	KeyE,
	KeyF,
	KeyG,
	KeyH,
	KeyI,
	KeyJ,
	KeyK,
	KeyL,
	KeyM,
	KeyN,
	KeyO,
	KeyP,
	KeyQ,
	KeyR,
	KeyS,
	KeyT,
	KeyU,
	KeyV,
	KeyW,
	KeyX,
	KeyY,
	KeyZ,
	Key0,
	Key1,
	Key2,
	Key3,
	Key4,
	Key5,
	Key6,
	Key7,
	Key8,
	Key9,
	KeyF1,
	KeyF2,
	KeyF3,
	KeyF4,
	KeyF5,
	KeyF6,
	KeyF7,
	KeyF8,
	KeyF9,
	KeyF10,
	KeyF11,
	KeyF12,
};

enum MouseButton
{
	MouseButtonLeft,
	MouseButtonMiddle,
	MouseButtonRight
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