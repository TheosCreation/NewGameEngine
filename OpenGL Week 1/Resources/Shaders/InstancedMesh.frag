#version 460 core

in vec2 FragTexcoord;
in vec3 FragNormal;
in vec3 FragPos;

uniform sampler2D tex1;
uniform float AmbientStrength		= 0.15f;
uniform vec3 AmbientColor			= vec3(1.0f, 1.0f, 1.0f);

uniform vec3 LightColor				= vec3(1.0f, 1.0f, 1.0f);
uniform vec3 LightPos				= vec3(-300.0f, 000.0f, 100.0f);

uniform vec3 CameraPos;
uniform float LightSpecularStrength = 1.0f;
uniform float ObjectShininess		= 32.0f;

// Out
out vec4 FinalColor;

void main()
{
	vec3 Ambient = AmbientStrength * AmbientColor;

	vec3 Normal = normalize(FragNormal);
	vec3 LightDir = normalize(FragPos - LightPos);

	float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
	vec3 Diffuse = DiffuseStrength * LightColor;

	// Specular Component
	vec3 ReverseViewDir = normalize(CameraPos - FragPos);
	vec3 HalfwayVector = normalize(-LightDir + ReverseViewDir);
	float SpecularReflectivity = pow(max(dot(Normal, HalfwayVector), 0.0f), ObjectShininess);
	vec3 Specular = LightSpecularStrength * SpecularReflectivity * LightColor;
	
	// Combine the lighting components
	vec4 Light = vec4(Ambient + Diffuse + Specular, 1.0f);

	FinalColor = Light * texture(tex1, FragTexcoord);
}