#version 460 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

out vec2 texCoord;
out vec3 FragColor;


void main(void)
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);

    FragColor = vec3(vertexTexCoords, 1.0);
}