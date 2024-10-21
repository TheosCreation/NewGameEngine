#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

uniform mat4 ModelMatrix;
uniform mat4 VPMatrix;

out vec2 FragTexcoord;
out vec3 FragPos;

void main()
{
    gl_Position = VPMatrix * ModelMatrix * vec4(vertexPosition, 1.0f);
    FragTexcoord = vertexTexCoords;
    FragPos = vec3(ModelMatrix * vec4(vertexPosition, 1.0f));
}