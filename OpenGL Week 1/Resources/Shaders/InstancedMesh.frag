#version 460 core

in vec2 FragTexcoord;
in vec3 FragNormal;
in vec3 FragPos;

uniform sampler2D tex1;
uniform float AmbientStrength		= 0.15f;
uniform vec3 AmbientColor			= vec3(1.0f, 1.0f, 1.0f);

uniform vec3 LightColor				= vec3(1.0f, 1.0f, 1.0f);
uniform vec3 LightPos				= vec3(-300.0f, 000.0f, 100.0f);

// Out
out vec4 FinalColor;

void main()
{
	vec3 Ambient = AmbientStrength * AmbientColor;

	vec4 Light = vec4(Ambient, 1.0f);

	FinalColor = Light * texture(tex1, FragTexcoord);
}