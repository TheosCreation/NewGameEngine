#version 460 core

uniform UniformData
{
    float scale;
};

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

layout (location = 0) out vec3 FragColor;

void main()
{
	gl_Position = vec4(Position * scale, 1.0f);
	FragColor = Color;
}