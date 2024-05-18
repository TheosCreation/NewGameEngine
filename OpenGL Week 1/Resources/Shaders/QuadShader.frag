#version 460 core

in vec2 FragTexcoord;

uniform sampler2D tex1;

// Out
out vec4 FinalColor;

void main()
{
	FinalColor = texture(tex1, FragTexcoord);
}