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
#include "Math.h"

// Forward declarations of classes

class UniformBuffer;
class VertexArrayObject;
class Shader;
class Texture2D;
class TextureCubeMap;
class ResourceManager;
class Resource;
class Texture;
class HeightMap;
class Mesh;
class InstancedMesh;

// Type definitions for variables
typedef unsigned int uint;
typedef glm::mat4 Mat4;
typedef glm::quat Quaternion;
typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;

// Type definitions for shared pointers
typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;
typedef std::shared_ptr<TextureCubeMap> TextureCubeMapPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<InstancedMesh> InstancedMeshPtr;
typedef std::shared_ptr<HeightMap> HeightMapPtr;

using std::shared_ptr;
using std::unique_ptr;

struct Transform
{
    Vector3 position;   // Position of the object in world space
    Quaternion rotation;   // Rotation of the object in world space
    Vector3 scale;      // Scale of the object in world space

    Transform()
        : position(Vector3(0.0f, 0.0f, 0.0f)),
        rotation(Quaternion(1.0f, 0.0f, 0.0f, 0.0f)),
        scale(Vector3(1.0f, 1.0f, 1.0f))
    {
    }

    Mat4 GetMatrix() const
    {
        Mat4 translationMatrix = glm::translate(Mat4(1.0f), position);
        Mat4 rotationMatrix = glm::toMat4(rotation);
        Mat4 scaleMatrix = glm::scale(Mat4(1.0f), scale);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }

    void SetPosition(const Vector3& newPosition)
    {
        position = newPosition;
    }

    void SetRotation(const Quaternion& newRotation)
    {
        rotation = newRotation;
    }

    void SetScale(const Vector3& newScale)
    {
        scale = newScale;
    }

    void Translate(const Vector3& translation)
    {
        position += translation;
    }

    void Rotate(const Quaternion& deltaRotation)
    {
        rotation = glm::normalize(deltaRotation * rotation);
    }

    void Scale(const Vector3& scaleFactor)
    {
        scale *= scaleFactor;
    }

    Vector3 GetForward() const
    {
        return rotation * Vector3(0.0f, 0.0f, 1.0f);
    }

    Vector3 GetRight() const
    {
        return rotation * Vector3(1.0f, 0.0f, 0.0f);
    }

    Vector3 GetUp() const
    {
        return rotation * Vector3(0.0f, 1.0f, 0.0f);
    }
};

struct Vertex
{
    Vector3 position;
    Vector2 texCoords;
    Vector3 normal;
};

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
    Mat4 viewMatrix; //View matrix
    Mat4 projectionMatrix; //Projection matrix
    Mat4 uiViewMatrix; //UI view matrix
    Mat4 uiProjectionMatrix; //UI projection matrix
    float currentTime; //Current time
    Vector3 cameraPosition; //Camera Position
};

// Struct representing a texture 2D description
struct Texture2DDesc
{
    unsigned char* textureData = nullptr; //Pointer to the texture data
    Rect textureSize = {}; //Size of the texture
    uint numChannels = 0; //Number of channels in the texture
};

struct HeightMapInfo {
    std::string filePath = "";
    uint width = 0;
    uint depth = 0;
    float cellSpacing = 1.0f;
};

// Struct representing a height map description
struct HeightMapDesc
{
    std::vector<float> data;
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

// Enum representing blend types
enum class BlendType
{
    Zero,
    One,
    SrcColor,
    OneMinusSrcColor,
    DstColor,
    OneMinusDstColor,
    SrcAlpha,
    OneMinusSrcAlpha,
    DstAlpha,
    OneMinusDstAlpha,
    ConstantColor,
    OneMinusConstantColor,
    ConstantAlpha,
    OneMinusConstantAlpha
};

enum class TextureType
{
    Default,
    Heightmap
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

enum class StencilOperationType
{
    Set,
    ResetNotEqual,
    ResetAlways
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

// Struct of predefined color constants.
struct Color {
    static constexpr Vector3 Red = Vector3(1.0f, 0.0f, 0.0f);
    static constexpr Vector3 Green = Vector3(0.0f, 1.0f, 0.0f);
    static constexpr Vector3 Blue = Vector3(0.0f, 0.0f, 1.0f);
    static constexpr Vector3 White = Vector3(1.0f, 1.0f, 1.0f);
};

// Struct representing a directional light
struct DirectionalLight
{
    Vector3 Direction;
    Vector3 Color;
    float SpecularStrength;
};

// Struct representing a point light
struct PointLight
{
    Vector3 Position;
    Vector3 Color;
    float SpecularStrength;

    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
};

// Struct representing a spot light
struct SpotLight
{
    Vector3 Position;
    Vector3 Direction;
    Vector3 Color;
    float SpecularStrength;
    float CutOff;
    float OuterCutOff;

    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
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