/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Resource.h
Description : Resource class represents a generic resource such as a file, image or texture
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <map>
#include <string>
#include "Utils.h"

class ResourceManager;
class Resource
{
public:
	Resource(const wchar_t* path, ResourceManager* manager);
	virtual ~Resource();

	std::wstring getPath();
protected:
	std::wstring m_path;

};