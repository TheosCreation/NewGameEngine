#version 460 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

uniform float CurrentTime;

out vec3 FragColor;

void main()
{
	gl_Position = vec4(Position * abs(sin(CurrentTime)), 1.0f);
	FragColor = Color;
}