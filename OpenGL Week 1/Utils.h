/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Utils.h
Description : header file that represents a utility header to structure this project to make it more readable
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <glm.hpp>
#include "Rect.h"

// Forward declarations of classes

class UniformBuffer;
class VertexArrayObject;
class Shader;
class Texture2D;
class TextureCubeMap;
class ResourceManager;
class Resource;
class Texture;
class Mesh;
class InstancedMesh;

// Type definitions for variables
typedef unsigned int uint;

// Type definitions for shared pointers
typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;
typedef std::shared_ptr<TextureCubeMap> TextureCubeMapPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<InstancedMesh> InstancedMeshPtr;

// Struct representing a vertex attribute
struct VertexAttribute
{
    uint numElements = 0; //Number of elements in the vertex attribute
};

// Struct representing a vertex buffer description
struct VertexBufferDesc
{
    void* verticesList = nullptr; //Pointer to the list of vertices
    uint vertexSize = 0; //Size of a single vertex
    uint listSize = 0; //Size of the vertex list

    VertexAttribute* attributesList = nullptr; //Pointer to the list of vertex attributes
    uint attributesListSize = 0; //Size of the vertex attributes list
};

// Struct representing an index buffer description
struct IndexBufferDesc
{
    void* indicesList = nullptr; //Pointer to the list of indices
    uint listSize = 0; //Size of the index list
};

// Struct representing a shader description
struct ShaderDesc
{
    const wchar_t* vertexShaderFileName; //Filename of the vertex shader
    const wchar_t* fragmentShaderFileName; //Filename of the fragment shader
};

// Struct representing a uniform buffer description
struct UniformBufferDesc
{
    uint size = 0; //Size of the uniform buffer
};

// Struct representing uniform data
struct UniformData
{
    glm::mat4 viewMatrix; //View matrix
    glm::mat4 projectionMatrix; //Projection matrix
    glm::mat4 uiViewMatrix; //UI view matrix
    glm::mat4 uiProjectionMatrix; //UI projection matrix
    float currentTime; //Current time
    glm::vec3 cameraPosition; //Camera Position
};

// Struct representing a texture 2D description
struct Texture2DDesc
{
    void* textureData = nullptr; //Pointer to the texture data
    Rect textureSize = {}; //Size of the texture
    uint numChannels = 0; //Number of channels in the texture
};

// Struct representing a texture Cubemap description
struct TextureCubeMapDesc
{
    std::vector<void*> textureData; // Pointers to the texture data for each face
    Rect textureSize = {}; // Size of each texture face
    uint numChannels = 0; // Number of channels in each texture face
};

// Enum representing camera types
enum class CameraType
{
    Orthogonal = 0, //Orthogonal camera
    Perspective //Perspective camera
};

// Enum representing triangle types
enum class TriangleType
{
    TriangleList = 0, //Triangle list
    TriangleStrip //Triangle strip
};

// Enum representing cull types
enum class CullType
{
    BackFace = 0, //Cull back face
    FrontFace, //Cull front face
    Both, //Cull both faces
    None //Cull no faces
};

// Enum representing depth types
enum class DepthType
{
    Never,
    Less,
    Equal,
    LessEqual,
    Greater,
    NotEqual,
    GreaterEqual,
    Always
};

// Enum representing winding orders
enum class WindingOrder
{
    ClockWise = 0, //Clockwise winding order
    CounterClockWise //Counter-clockwise winding order
};

// Enum representing shader types
enum class ShaderType
{
    VertexShader = 0, //Vertex shader
    FragmentShader //Fragment shader
};

// Enum representing key codes
enum Key
{
    Key0 = 48,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    KeyA = 65,
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
    KeyF1 = 290,
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
    KeyEscape = 256,
    KeyRight = 262,
    KeyLeft,
    KeyDown,
    KeyUp,
    KeyShift = 340,
};

// Enum representing mouse buttons
enum MouseButton
{
    MouseButtonLeft, //Left mouse button
    MouseButtonRight, //Right mouse button
    MouseButtonMiddle, //Middle mouse button
};

struct DirectionalLight
{
    glm::vec3 Direction;
    glm::vec3 Color;
    float SpecularStrength;
};

struct PointLight
{
    glm::vec3 Position;
    glm::vec3 Color;
    float SpecularStrength;
};

// Macro for throwing an OpenGL error
#define OGL3D_ERROR(message)\
{\
	std::stringstream m;\
	m << "OGL3D Error: " << message << std::endl;\
	throw std::runtime_error(m.str());\
}

// Macro for logging an OpenGL warning
#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

// Macro for logging OpenGL information
#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;