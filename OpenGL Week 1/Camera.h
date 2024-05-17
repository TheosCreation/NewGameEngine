/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Camera.h
Description : implements a camera for opengl orbits the center of the world
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include "Entity.h"
#include "Math.h"
#include "Rect.h"

class Camera : public Entity
{
public:
	void getViewMatrix(glm::mat4& view);
	void getProjectionMatrix(glm::mat4& proj);

	void setFarPlane(float farPlane);
	void setNearPlane(float nearPlane);
	void setFieldOfView(float fov);
	CameraType getCameraType();
	void setCameraType(const CameraType& type);
	void setScreenArea(const Rect& screen);
	void setTargetPosition(glm::vec3 newTargetPosition);
private:
	void computeProjectionMatrix();
private:
	glm::mat4 m_view{};
	glm::mat4 m_projection{};
	glm::vec3 m_targetPosition{};

	float m_farPlane = 100000.0f;
	float m_nearPlane = 0.01f;
	float m_fov = 90.0f;
	const float radius = 10.0f;
	CameraType m_type = CameraType::Perspective;
	Rect m_screenArea;
};

