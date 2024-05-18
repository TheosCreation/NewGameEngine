/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : GraphicsEngine.h
Description : GraphicsEngine class contains all the render functionality of opengl
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Utils.h"
#include "Math.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();

	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc);
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	ShaderPtr createShader(const ShaderDesc& desc);
	Texture2DPtr createTexture2D(const Texture2DDesc& desc);

	void clear(const glm::vec4& color);
	void setFaceCulling(const CullType& type);
	void setWindingOrder(const WindingOrder& type);
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setShader(const ShaderPtr& program);
	void setTexture2D(const Texture2DPtr& texture, uint slot);

	void drawTriangles(const TriangleType& triangleType, uint vertexCount, uint offset);
	void drawIndexedTriangles(const TriangleType& triangleType, uint indicesCount);
	void drawIndexedTrianglesInstanced(const TriangleType& triangleType, uint indicesCount, int instanceCount);
};

