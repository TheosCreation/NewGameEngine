#pragma once
#include "Prerequisites.h"
#include "Vec4.h"
#include "ShaderLoader.h"
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
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferData& data);
public:
	void InitialSetup();
	void SetViewport(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	//void MakeTriangle(GLuint* VB0, GLuint* VA0, GLfloat* vertices, GLsizei numVertices);
	void drawTriangles(unsigned int vertexCount, unsigned int offset);
	void Render(GLFWwindow* WindowToRenderTo);
	void clear(const Vec4& color);
	void Update();

private:
};

