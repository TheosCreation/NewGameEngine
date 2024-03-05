#pragma once
#include <map>
#include <string>
#include "Prerequisites.h"

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

