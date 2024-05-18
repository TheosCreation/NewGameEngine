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
#include "QuadEntity.h"

class MyPlayer : public Entity
{
public:
	MyPlayer();
	~MyPlayer();

	virtual void onCreate();
	virtual void onUpdate(float deltaTime);
	void setCameraPosition(glm::vec3 newPosition);

	void addButtonRef(QuadEntity* buttonRef);

	void setButtonTextures(TexturePtr buttonUpTexture, TexturePtr buttonHoveringTexture, TexturePtr buttonDownTexture);

	void setInstancedEntity(InstancedMeshEntity* instancedEntityRef, TexturePtr texture1, TexturePtr texture2);

private:
	float m_elapsedSeconds = 0.0f;
	Entity* m_entity = nullptr;

	glm::vec3 m_camPosition{};

	// movement speed of the moveable object
	float m_movementSpeed = 50.0f;

	// speed of the orbiting camera
	float m_rotationSpeed = 5.0f;
	// speed the camera shorten or lengthens the orbit radius
	float m_zoomSpeed = 20.0f;

	float m_originalOrbitSpeed = 5.0f;
	float m_orbitSpeed = m_originalOrbitSpeed;
	float m_orbitHorizontal = 0.0f;
	float m_minimumOrbitalRadius = 35.0f;
	float m_maximumOrbitalRadius = 500.0f;
	float m_orbitRadius = 40.0f;
	float m_inactivityTimer = 1.0f; 
	
	bool m_autoRotate = false;
	bool m_playMode = false;
	bool m_wireframeMode = false;

	Camera* m_cam = nullptr;
	Camera* m_uiCamera = nullptr;
	InputManager* input = nullptr;

	std::vector<QuadEntity*> m_buttonRefs;
	InstancedMeshEntity* m_instancedEntity;
	TexturePtr m_instancedEntityTexture1Ptr;
	TexturePtr m_instancedEntityTexture2Ptr;

	TexturePtr m_buttonUpTexture;
	TexturePtr m_buttonHoveringTexture;
	TexturePtr m_buttonDownTexture;
	bool m_instancedTextureSwitched;
	bool m_buttonTextureSwitched;
};

