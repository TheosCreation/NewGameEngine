#version 460 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 modelMatrix;
uniform mat4 VPMatrix;

out vec2 FragTexcoord;

void main(void)
{
    gl_Position = VPMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
    FragTexcoord = vertexTexCoords;
}