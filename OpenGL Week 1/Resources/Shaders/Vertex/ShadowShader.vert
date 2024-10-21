#version 460 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 ModelMatrix;
uniform mat4 VPLight;

void main()
{
    gl_Position = VPLight * ModelMatrix * vec4(vertexPosition, 1.0f);
}