#pragma once
#include "Utils.h"
#include "Math.h"
#include "UniformBuffer.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Rect.h"

//extern float CurrentTime;

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

public:	
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc);
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	UniformBufferPtr createUniform(const UniformBufferDesc& desc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);
	Texture2DPtr createTexture2D(const Texture2DDesc& desc);
public:
	void clear(const glm::vec4& color);
	void setFaceCulling(const CullType& type);
	void setWindingOrder(const WindingOrder& type);
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setUniformBuffer(const UniformBufferPtr& buffer, uint slot);
	void setShaderProgram(const ShaderProgramPtr& program);
	void setTexture2D(const Texture2DPtr& texture, uint slot);

	void drawTriangles(const TriangleType& triangleType, uint vertexCount, uint offset);
	void drawIndexedTriangles(const TriangleType& triangleType, uint indicesCount);

private:
};

