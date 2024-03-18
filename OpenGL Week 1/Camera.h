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
	void setCameraType(const CameraType& type);
	void setScreenArea(const Rect& screen);
private:
	void computeProjectionMatrix();
private:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	float m_farPlane = 100.0f;
	float m_nearPlane = 0.001f;
	float m_fov = 90.0f;
	CameraType m_type = CameraType::Perspective;
	Rect m_screenArea;
};

