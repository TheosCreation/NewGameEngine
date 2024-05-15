#version 460 core

uniform mat4 mvpMatrixs[256];

out vec2 outTexcoord;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

void main(void)
{
    gl_Position = mvpMatrixs[gl_InstanceID] * vec4(vertexPosition, 1.0);
    outTexcoord = vertexTexCoords;
}
