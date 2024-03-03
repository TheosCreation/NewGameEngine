#include "Camera.h"

void Camera::getViewMatrix(Mat4& view)
{
	//invert the world matrix in order to get the view matrix
	m_view = m_world;
	m_view.inverse();
	view = m_view;
}

void Camera::getProjectionMatrix(Mat4& proj)
{
	proj = m_projection;
}

void Camera::setFarPlane(float farPlane)
{
	m_farPlane = farPlane;
	computeProjectionMatrix();
}

void Camera::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
	computeProjectionMatrix();
}

void Camera::setFieldOfView(float fov)
{
	m_fov = fov;
	computeProjectionMatrix();
}

void Camera::setCameraType(const CameraType& type)
{
	m_type = type;
	computeProjectionMatrix();
}

void Camera::setScreenArea(const Rect& screen)
{
	m_screenArea = screen;
	computeProjectionMatrix();
}

void Camera::computeProjectionMatrix()
{
	if (m_type == CameraType::Perspective)
		m_projection.setPerspectiveFovLH(m_fov, (float)m_screenArea.width / (float)m_screenArea.height, m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection.setOrthoLH((float)m_screenArea.width * 0.013f, (float)m_screenArea.height * 0.013f, m_nearPlane, m_farPlane);
}
