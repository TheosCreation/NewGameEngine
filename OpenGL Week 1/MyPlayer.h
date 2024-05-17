/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : MyPlayer.h
Description : MyPlayer class is a entity that can be adjusted by the user
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "All.h"
#include "InstancedMeshEntity.h"

class MyPlayer : public Entity
{
public:
	MyPlayer();
	~MyPlayer();

	virtual void onCreate();
	virtual void onUpdate(float deltaTime);
	void setCameraPosition(glm::vec3 newPosition);

	void addButtonRef(Entity* buttonRef);

	void setInstancedEntity(InstancedMeshEntity* instancedEntityRef, TexturePtr texture1, TexturePtr texture2);

private:
	float m_elapsedSeconds = 0.0f;
	Entity* m_entity = nullptr;

	glm::vec3 m_camPosition{};

	float m_movementSpeed = 50.0f;
	float m_rotationSpeed = 5.0f;

	float m_zoomSpeed = 5.0f;
	float m_originalOrbitSpeed = 5.0f;
	float m_orbitSpeed = m_originalOrbitSpeed;
	float m_orbitHorizontal = 0.0f;
	float m_minimumOrbitalRadius = 5.0f;
	float m_maximumOrbitalRadius = 50.0f;
	float m_orbitRadius = 20.0f;
	float m_inactivityTimer = 1.0f; 
	
	bool m_autoRotate = false;
	bool m_playMode = false;
	bool m_wireframeMode = false;

	Camera* m_cam = nullptr;
	Camera* m_uiCamera = nullptr;
	InputManager* input = nullptr;

	std::vector<Entity*> m_buttonRefs;
	InstancedMeshEntity* m_instancedEntity;
	TexturePtr m_texture1Ptr;
	TexturePtr m_texture2Ptr;
	bool m_switched;
};

