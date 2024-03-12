#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

inline glm::vec3 getForwardDirection(glm::mat4 matrix)
{
    glm::vec3 forwardDir(matrix[2][0], matrix[2][1], matrix[2][2]);
    return glm::normalize(forwardDir);
}

inline glm::vec3 getRightwardDirection(glm::mat4 matrix)
{
    glm::vec3 rightwardDir(matrix[0][0], matrix[0][1], matrix[0][2]);
    return glm::normalize(rightwardDir);
}