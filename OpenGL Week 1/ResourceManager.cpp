#include "ResourceManager.h"
#include "Texture.h"
#include "Mesh.h"
#include "InstancedMesh.h"
#include <filesystem>

ResourceManager::ResourceManager(Game* game)
{
	m_game = game;
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::createResourceFromFile(const wchar_t* path, bool instancing)
{
	//check if the texture we want to load has been already loaded.
	auto it = m_mapResources.find(path);

	if (it != m_mapResources.end())
	{
		return it->second;
	}

	//the texture has not been loaded yet. Let's load it.
	std::filesystem::path resPath = path;
	if (!std::filesystem::exists(resPath)) return ResourcePtr(); // check if the file exists

	auto ext = resPath.extension();

	// if the resource we want to load has one of these extensions
	if (!ext.compare(L".jpg") || !ext.compare(L".png") || !ext.compare(L".bmp") || !ext.compare(L".tga"))
	{
		//let's create a texture resource
		auto texturePtr = std::make_shared<Texture>(resPath.c_str(), this);
		if (texturePtr)
		{
			m_mapResources.emplace(path, texturePtr);
			return texturePtr;
		}
	}
	else if (!ext.compare(L".obj") && instancing)
	{
		auto instancedMeshPtr = std::make_shared<InstancedMesh>(resPath.c_str(), this);
		if (instancedMeshPtr)
		{
			m_mapResources.emplace(path, instancedMeshPtr);
			return instancedMeshPtr;
		}
	}
	else
	{
		auto meshPtr = std::make_shared<Mesh>(resPath.c_str(), this);
		if (meshPtr)
		{
			m_mapResources.emplace(path, meshPtr);
			return meshPtr;
		}
	}

	return ResourcePtr();
}

Game* ResourceManager::getGame()
{
    return m_game;
}
