#pragma once
#include "Entity.h"
#include "Mat4.h"
#include "Rect.h"

class Camera : public Entity
{
public:
	void getViewMatrix(Mat4& view);
	void getProjectionMatrix(Mat4& proj);

	void setFarPlane(float farPlane);
	void setNearPlane(float nearPlane);
	void setFieldOfView(float fov);
	void setCameraType(const CameraType& type);
	void setScreenArea(const Rect& screen);
private:
	void computeProjectionMatrix();
private:
	Mat4 m_view;
	Mat4 m_projection;

	float m_farPlane = 100.0f;
	float m_nearPlane = 0.001f;
	float m_fov = 1.3f;
	CameraType m_type = CameraType::Perspective;
	Rect m_screenArea;
};

