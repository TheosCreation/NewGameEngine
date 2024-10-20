#version 460 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 VPMatrix;

void main()
{
    gl_Position = VPMatrix * vec4(vertexPosition.xyz, 1.0f);
}