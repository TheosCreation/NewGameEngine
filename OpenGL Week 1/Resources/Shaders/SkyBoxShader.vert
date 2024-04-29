#version 460 core

uniform mat4 mvpMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

layout out vec2 outTexcoord;


void main(void)
{
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);

    outTexcoord = vertexTexCoords;
}