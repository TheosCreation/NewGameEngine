#pragma once
#include "Prerequisites.h"

class EntitySystem;
class Entity
{
public:
	Entity();
	virtual ~Entity();

	void release();

	EntitySystem* getEntitySystem();
protected:
	virtual void onCreate() {}
	virtual void onUpdate(float deltaTime) {}

protected:
	size_t m_id = 0;
	EntitySystem* m_entitySystem = nullptr;

	friend class EntitySystem;
};
