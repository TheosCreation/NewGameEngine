#version 460 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 ModelMatrix;
uniform mat4 VPMatrix;

void main()
{
    gl_Position = VPMatrix * ModelMatrix * vec4(vertexPosition, 1.0f);
}