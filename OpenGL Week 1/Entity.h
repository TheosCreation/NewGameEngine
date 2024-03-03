#pragma once
#include "Prerequisites.h"
#include "Vec3.h"
#include "Mat4.h"
#include "Game.h"

class EntitySystem;
class Game;
class Entity
{
public:
	Entity();
	virtual ~Entity();
public:
	void setPosition(const Vec3& position);
	void setRotation(const Vec3& rotation);
	void setScale(const Vec3& scale);
	Vec3 getPosition();
	Vec3 getRotation();
	Vec3 getScale();

	EntitySystem* getEntitySystem();
	Game* getGame();
	void getWorldMatrix(Mat4& world);
	void release();
protected:
	virtual void onCreate() {}
	virtual void onUpdate(float deltaTime) {}
	void processWorldMatrix();

protected:
	Mat4 m_world; 
	
	Vec3 m_position;
	Vec3 m_rotation;
	Vec3 m_scale = Vec3(1, 1, 1);

	size_t m_id = 0;
	EntitySystem* m_entitySystem = nullptr;
	Game* m_game = nullptr;

	friend class EntitySystem;
	friend class Game;
};
