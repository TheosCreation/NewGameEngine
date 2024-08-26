/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : GraphicsEntity.cpp
Description : Entity type to be rendered by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "GraphicsEntity.h"
#include "GraphicsEngine.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"

GraphicsEntity::GraphicsEntity()
{
}

GraphicsEntity::~GraphicsEntity()
{
}
void GraphicsEntity::ProcessUniformData(const std::string& name, const std::any& value) {
    if (value.type() == typeid(int)) {
        m_shader->setInt(name, std::any_cast<int>(value));
    }
    else if (value.type() == typeid(uint)) {
        m_shader->setUint(name, std::any_cast<uint>(value));
    }
    else if (value.type() == typeid(float)) {
        m_shader->setFloat(name, std::any_cast<float>(value));
    }
    else if (value.type() == typeid(glm::vec3)) {
        m_shader->setVec3(name, std::any_cast<glm::vec3>(value));
    }
    else if (value.type() == typeid(glm::vec2)) {
        m_shader->setVec2(name, std::any_cast<glm::vec2>(value));
    }
    else if (value.type() == typeid(Mat4)) {
        m_shader->setMat4(name, std::any_cast<Mat4>(value));
    }
    else {
        std::cerr << "Unknown type for uniform: " << name << std::endl;
    }
}

void GraphicsEntity::ProcessTextureData(const std::string& name, const std::tuple<TexturePtr, uint>& value)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    auto [texture, slot] = value;

    if (std::dynamic_pointer_cast<Texture2D>(texture)) {
        graphicsEngine.setTexture2D(texture, slot, name);
    }
    else if (std::dynamic_pointer_cast<TextureCubeMap>(texture))
    {
        graphicsEngine.setTextureCubeMap(texture, slot, name);
    }
    else
    {
        std::cerr << "Unsupported texture type for key: " << name << std::endl;
    }
}

void GraphicsEntity::onGraphicsUpdate(UniformData data)
{
    auto& graphicsEngine = GraphicsEngine::GetInstance();
    graphicsEngine.setFaceCulling(CullType::BackFace);
    graphicsEngine.setWindingOrder(WindingOrder::CounterClockWise);
    graphicsEngine.setDepthFunc(DepthType::Less);
    graphicsEngine.setShader(m_shader);
}

ShaderPtr GraphicsEntity::getShader() const
{
	return m_shader;
}

void GraphicsEntity::setShader(const ShaderPtr& shader)
{
	m_shader = shader;
}

TexturePtr GraphicsEntity::getTexture() const
{
	return m_texture;
}

void GraphicsEntity::setTexture(const TexturePtr& texture)
{
	m_texture = texture;
}

void GraphicsEntity::setHeightMap(const TexturePtr& heightMapTexture)
{
    m_heightMap = heightMapTexture;
}

void GraphicsEntity::setColor(Vector3 color)
{
	m_color = color;
}