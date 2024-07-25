/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Camera.cpp
Description : Implements a camera for OpenGL
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#include "Camera.h"
#include "EntitySystem.h"

void Camera::getViewMatrix(glm::mat4& view)
{
	if (m_type == CameraType::Perspective)
	{
		m_view = glm::lookAt(m_position, m_position + m_forwardDirection, m_upwardDirection);
	}
	else if (m_type == CameraType::Orthogonal)
	{
		glm::vec3 cameraPosition = glm::vec3(m_screenArea.width, -m_screenArea.height, 1.0f);
		glm::vec3 targetPosition = glm::vec3(m_screenArea.width, -m_screenArea.height, 0.0f);
		m_view = glm::lookAt(cameraPosition, targetPosition, m_upwardDirection);
	}
	view = m_view;
}

void Camera::getProjectionMatrix(glm::mat4& proj) const
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

void Camera::setTargetPosition(glm::vec3 newTargetPosition)
{
	m_targetPosition = newTargetPosition;
}

glm::vec3 Camera::getForwardDirection()
{
	return m_forwardDirection;
}

void Camera::setForwardDirection(glm::vec3 newForwardDirection)
{
	m_forwardDirection = newForwardDirection;
}


glm::vec3 Camera::getUpwardDirection()
{
	return m_upwardDirection;
}

glm::vec3 Camera::getRightwardDirection()
{
	glm::vec3 right = glm::normalize(glm::cross(m_forwardDirection, m_worldUp));
	return right;
}

void Camera::setUpwardDirection(glm::vec3 newUpwardDirection)
{
	m_upwardDirection = newUpwardDirection;
}

void Camera::computeProjectionMatrix()
{
	if (m_type == CameraType::Perspective)
		m_projection = glm::perspective(glm::radians(m_fov), (float)m_screenArea.width / (float)m_screenArea.height, m_nearPlane, m_farPlane);
	else if (m_type == CameraType::Orthogonal)
		m_projection = glm::ortho(-(float)m_screenArea.width, (float)m_screenArea.width, -(float)m_screenArea.height, (float)m_screenArea.height, m_nearPlane, m_farPlane);
}
