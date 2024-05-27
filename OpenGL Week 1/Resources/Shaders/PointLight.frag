#version 460 core

uniform vec3 uColor;

// Out
out vec4 FinalColor;

void main()
{
    // Calculate the final color
    FinalColor = vec4(uColor, 1.0f);
}