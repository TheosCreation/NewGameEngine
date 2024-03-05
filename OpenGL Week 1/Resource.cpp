#include "Resource.h"

Resource::Resource(const wchar_t* path, ResourceManager* manager):m_path(path)
{
}

Resource::~Resource()
{
}

std::wstring Resource::getPath()
{
	return m_path;
}
