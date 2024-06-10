/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : GraphicsEntity.h
Description : Entity type to be rendered by the graphics engine
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Entity.h"
#include "Rect.h"
#include "Texture.h"
#include "Shader.h"

// Forward declaration of EntitySystem class
class EntitySystem;

/**
 * @class GraphicsEntity
 * @brief An entity type to be rendered by the graphics engine.
 */
class GraphicsEntity : public Entity
{
public:
    /**
     * @brief Constructor for the GraphicsEntity class.
     */
    GraphicsEntity();

    /**
     * @brief Destructor for the GraphicsEntity class.
     */
    virtual ~GraphicsEntity();

    /**
     * @brief Called every frame to update the graphics.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onGraphicsUpdate(float deltaTime) {}

    /**
     * @brief Sets the uniform data for the shader.
     * @param data The uniform data to set.
     */
    virtual void setUniformData(UniformData data) {};

    /**
     * @brief Gets the shader used by this entity.
     * @return A shared pointer to the shader.
     */
    ShaderPtr getShader() const;

    /**
     * @brief Sets the shader to be used by this entity.
     * @param shader A shared pointer to the shader.
     */
    void setShader(const ShaderPtr& shader);

    /**
     * @brief Gets the texture used by this entity.
     * @return A shared pointer to the texture.
     */
    TexturePtr getTexture() const;

    /**
     * @brief Sets the texture to be used by this entity.
     * @param texture A shared pointer to the texture.
     */
    void setTexture(const TexturePtr& texture);

    /**
     * @brief Sets the color to be used by this entity.
     * @param color A vec3 of rgb values.
     */
    void setColor(glm::vec3 color);

protected:
    ShaderPtr m_shader; //The shader used by this entity
    glm::vec3 m_color;
    TexturePtr m_texture; //The texture used by this entity
};