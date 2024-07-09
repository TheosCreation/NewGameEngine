/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Camera.h
Description : Implements a camera for OpenGL
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
    /**
     * @brief Gets the view matrix for the camera.
     * @param[out] view The view matrix to fill.
     */
    void getViewMatrix(glm::mat4& view);

    /**
     * @brief Gets the projection matrix for the camera.
     * @param[out] proj The projection matrix to fill.
     */
    void getProjectionMatrix(glm::mat4& proj) const;

    /**
     * @brief Sets the far plane distance of the camera.
     * @param farPlane The distance to set.
     */
    void setFarPlane(float farPlane);

    /**
     * @brief Sets the near plane distance of the camera.
     * @param nearPlane The distance to set.
     */
    void setNearPlane(float nearPlane);

    /**
     * @brief Sets the field of view (FOV) angle of the camera.
     * @param fov The FOV angle in degrees.
     */
    void setFieldOfView(float fov);

    /**
     * @brief Gets the type of the camera (Perspective or Orthographic).
     * @return The camera type.
     */
    CameraType getCameraType();

    /**
     * @brief Sets the type of the camera (Perspective or Orthographic).
     * @param type The camera type to set.
     */
    void setCameraType(const CameraType& type);

    /**
     * @brief Sets the screen area of the camera.
     * @param screen The screen area rectangle.
     */
    void setScreenArea(const Rect& screen);

    /**
     * @brief Sets the target position that the camera is looking at.
     * @param newTargetPosition The new target position.
     */
    void setTargetPosition(glm::vec3 newTargetPosition);

    /**
     * @brief Gets the forward direction of the camera.
     * @return Forward vector of the camera.
     */
    glm::vec3 getForwardDirection();

    /**
     * @brief Sets the forward direction of the camera.
     * @param newForwardDirection The new forward direction.
     */
    void setForwardDirection(glm::vec3 newForwardDirection);

    /**
     * @brief Gets the upward direction of the camera.
     * @return Upward vector of the camera.
     */
    glm::vec3 getUpwardDirection();

    /**
     * @brief Sets the upward direction of the camera.
     * @param newUpwardDirection The new upward direction.
     */
    void setUpwardDirection(glm::vec3 newUpwardDirection);

private:
    /**
     * @brief Computes the projection matrix based on camera parameters.
     */
    void computeProjectionMatrix();

private:
    glm::mat4 m_view{};                 //The view matrix of the camera.
    glm::mat4 m_projection{};           //The projection matrix of the camera.
    glm::vec3 m_targetPosition{};       //The target position of the camera.
    glm::vec3 m_forwardDirection{0.0f, 0.0f, -1.0f};  //The forwards direction of the camera.
    glm::vec3 m_upwardDirection{ 0.0f, 1.0f, 0.0f };  //The upwards direction of the camera.

    float m_farPlane = 10000.0f;       //The distance of the far plane.
    float m_nearPlane = 0.1f;          //The distance of the near plane.
    float m_fov = 90.0f;                //The field of view (FOV) angle.
    const float radius = 10.0f;         //The radius of the camera's orbit.
    CameraType m_type = CameraType::Perspective;  //The type of the camera (Perspective or Orthographic).
    Rect m_screenArea;                   //The screen area of the camera.
};

