#include "Camera.h"
#include "EntitySystem.h"

void Camera::getViewMatrix(glm::mat4& view)
{
	m_view = glm::lookAt(m_position, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
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

CameraType Camera::getCameraType()
{
	return m_type;
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
		m_projection = glm::perspective(glm::radians(m_fov), (float)m_screenArea.width / (float)m_screenArea.height, m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection = glm::ortho(-(float)m_screenArea.width, (float)m_screenArea.width, -(float)m_screenArea.height, (float)m_screenArea.height, m_nearPlane, m_farPlane);
}
