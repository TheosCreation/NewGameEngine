#version 460 core

in vec2 FragTexcoord;

uniform sampler2D screenTexture;

// Out
out vec4 FinalColor;

void main()
{
	FinalColor = texture(screenTexture, FragTexcoord);
}