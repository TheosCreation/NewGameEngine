#include "Camera.h"

void Camera::getViewMatrix(glm::mat4& view)
{
	//invert the world matrix in order to get the view matrix
	m_view = glm::inverse(m_world);
	view = m_view;
}

void Camera::getProjectionMatrix(glm::mat4& proj)
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
		m_projection = glm::perspectiveLH(glm::radians(m_fov), (float)m_screenArea.width / (float)m_screenArea.height, m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection = glm::orthoLH(0.0f, (float)m_screenArea.width, (float)m_screenArea.height, 0.0f, m_nearPlane, m_farPlane);
}
