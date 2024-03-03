#pragma once
#include "Prerequisites.h"
#include <map>
#include <set>

class Entity;
class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();

public:
	template <typename T>
	T* createEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity class");
		auto id = typeid(T).hash_code();
		auto e = new T();
		if (createEntityInternal(e, id))
			return e;
		return nullptr;
	}

private:
	bool createEntityInternal(Entity* entity, size_t id);
	void removeEntity(Entity* entity);

	void update(float deltaTime);
private:
	std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> m_entities;
	std::set<Entity*> m_entitiesToDestroy;

	friend class Entity;
	friend class Game;
};
