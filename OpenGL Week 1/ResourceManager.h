/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : ResourceManager.h
Description : ResourceManager class manages the resources created with the resource class
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <map>
#include <string>
#include "Utils.h"

class Game;
class ResourceManager
{
public:
	ResourceManager(Game* game);
	virtual ~ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* path);

	Game* getGame();
protected:
	std::map<std::wstring, ResourcePtr> m_mapResources;
	Game* m_game = nullptr;
};