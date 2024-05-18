/***
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2023 Media Design School
File Name : Math.h
Description : allow other classes to include the glm libary and this header adds more specific required functionality
Author : Theo Morris
Mail : theo.morris@mds.ac.nz
**/

#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

inline glm::vec3 getBackwardDirection(glm::mat4 matrix)
{
    glm::vec3 backwardDir(matrix[2][0], matrix[2][1], matrix[2][2]);
    return backwardDir;
}

inline glm::vec3 getForwardDirection(glm::mat4 matrix)
{
    return -getBackwardDirection(matrix);
}

inline glm::vec3 getRightwardDirection(glm::mat4 matrix)
{
    glm::vec3 rightwardDir(matrix[0][0], matrix[0][1], matrix[0][2]);
    return rightwardDir;
}

inline glm::vec3 getDownwardDirection(glm::mat4 matrix)
{
    glm::vec3 downwardDir(matrix[1][0], matrix[1][1], matrix[1][2]);
    return downwardDir;
}

inline glm::vec3 getUpwardDirection(glm::mat4 matrix)
{
    return -getDownwardDirection(matrix);
}