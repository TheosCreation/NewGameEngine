#pragma once
#include <map>
#include <string>
#include "Prerequisites.h"

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

