#pragma once
#include "Utils.h"

class Shader;

class GeometryBuffer
{
public:
	/**
	 * @brief Static method to get the singleton instance of the GeometryBuffer class.
	 * @return The singleton instance of the GeometryBuffer.
	 */
	static GeometryBuffer& GetInstance()
	{
		static GeometryBuffer instance;
		return instance;
	}

	/**
	 * @brief Public constructor for the GeometryBuffer class.
	 */
	void Init(Vector2 _windowSize);

	// Delete copy constructor and assignment operator to prevent copying.
	GeometryBuffer(const GeometryBuffer&) = delete;
	GeometryBuffer& operator=(const GeometryBuffer&) = delete;

	void Bind();
	void UnBind();

	void WriteDepth();
	void PopulateShader(ShaderPtr _shader);
	void Resize(Vector2 _windowSize);

private:
	/**
	 * @brief Private contructor for the GeometryBuffer class.
	 */
	GeometryBuffer() = default;

	/**
	 * @brief Private destructor for the GeometryBuffer class.
	 */
	~GeometryBuffer() = default;

	Vector2 m_size = Vector2(0.0f);
	uint FBO = 0;

	uint Texture_Position = 0;
	uint Texture_Normal = 1;
	uint Texture_AlbedoShininess = 2;
	uint Texture_Depth = 3;
};

