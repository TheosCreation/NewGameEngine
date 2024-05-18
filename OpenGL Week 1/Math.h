/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name : Math.h
Description : allow other classes to include the glm library and this header adds more specific required functionality
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/**
 * @brief Gets the backward direction vector from a transformation matrix.
 * @param matrix The transformation matrix.
 * @return The backward direction vector.
 */
inline glm::vec3 getBackwardDirection(glm::mat4 matrix)
{
    glm::vec3 backwardDir(matrix[2][0], matrix[2][1], matrix[2][2]);
    return backwardDir;
}

/**
 * @brief Gets the forward direction vector from a transformation matrix.
 * @param matrix The transformation matrix.
 * @return The forward direction vector.
 */
inline glm::vec3 getForwardDirection(glm::mat4 matrix)
{
    return -getBackwardDirection(matrix);
}

/**
 * @brief Gets the rightward direction vector from a transformation matrix.
 * @param matrix The transformation matrix.
 * @return The rightward direction vector.
 */
inline glm::vec3 getRightwardDirection(glm::mat4 matrix)
{
    glm::vec3 rightwardDir(matrix[0][0], matrix[0][1], matrix[0][2]);
    return rightwardDir;
}

/**
 * @brief Gets the downward direction vector from a transformation matrix.
 * @param matrix The transformation matrix.
 * @return The downward direction vector.
 */
inline glm::vec3 getDownwardDirection(glm::mat4 matrix)
{
    glm::vec3 downwardDir(matrix[1][0], matrix[1][1], matrix[1][2]);
    return downwardDir;
}

/**
 * @brief Gets the upward direction vector from a transformation matrix.
 * @param matrix The transformation matrix.
 * @return The upward direction vector.
 */
inline glm::vec3 getUpwardDirection(glm::mat4 matrix)
{
    return -getDownwardDirection(matrix);
}