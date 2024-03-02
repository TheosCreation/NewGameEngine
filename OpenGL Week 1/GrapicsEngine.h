#pragma once
#include "Prerequisites.h"
#include <glew.h>
#include <glfw3.h>
#include "Vec4.h"
#include "Rect.h"

//extern GLfloat Vertices_Tri0[];
//
//extern GLfloat Vertices_Tri1[];
//
////init VAO's and VBO's here
//extern GLuint VBO_Tri0, VAO_Tri0;
//extern GLuint VBO_Tri1, VAO_Tri1;
//
//// init Shaders here
//extern GLuint Program_FixedTri;
//extern GLuint Program_PositionOnly;
//extern GLuint Program_VertexColor;
//extern GLuint Program_ColorFade;
//
//extern float CurrentTime;

class GrapicsEngine
{
public:
	GrapicsEngine();
	~GrapicsEngine();

public:	
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& data);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);
public:
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setShaderProgram(const ShaderProgramPtr& program);
	void drawTriangles(unsigned int vertexCount, unsigned int offset);
	void Render(GLFWwindow* WindowToRenderTo);
	void clear(const Vec4& color);
	void Update();

private:
};

