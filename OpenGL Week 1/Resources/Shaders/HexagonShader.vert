#version 460 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 rgb;

out vec3 FragColor;


void main(void)
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);

    FragColor = rgb;
}