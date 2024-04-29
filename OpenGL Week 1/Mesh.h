#pragma once
#include <map>
#include <string>
#include "Utils.h"
#include "Resource.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* path, ResourceManager* manager);
	virtual ~Mesh();

	VertexArrayObjectPtr getVertexArrayObject();

private:
	VertexArrayObjectPtr m_vao;
};