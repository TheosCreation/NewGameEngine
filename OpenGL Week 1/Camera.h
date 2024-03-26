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
private:
	void computeProjectionMatrix();
private:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_farPlane = 1000.0f;
	float m_nearPlane = 1.0f;
	float m_fov = 90.0f;
	const float radius = 10.0f;
	CameraType m_type = CameraType::Orthogonal;
	Rect m_screenArea;
};

