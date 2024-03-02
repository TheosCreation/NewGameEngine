#pragma once
#include "Prerequisites.h"
#include <glew.h>
#include <glfw3.h>
#include "Vec4.h"
#include "Rect.h"

//extern float CurrentTime;

class GrapicsEngine
{
public:
	GrapicsEngine();
	~GrapicsEngine();

public:	
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& data);
	UniformBufferPtr createUniform(const UniformBufferDesc& desc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);
public:
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setUniformBuffer(const UniformBufferPtr& buffer, uint slot);
	void setShaderProgram(const ShaderProgramPtr& program);
	void drawTriangles(const TriangleType& triangleType, uint vertexCount, uint offset);
	void Render(GLFWwindow* WindowToRenderTo);
	void clear(const Vec4& color);
	void Update();

private:
};

