#version 460 core

in vec3 FragColor;

out vec4 FinalColor;

void main()
{
	FinalColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	FinalColor.rgb = FragColor;
}
