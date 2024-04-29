#version 460 core

uniform mat4 mvpMatrix;

out vec2 outTexcoord;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

void main(void)
{
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
    outTexcoord = vertexTexCoords;
}
