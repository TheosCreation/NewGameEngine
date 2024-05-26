#version 460 core
#define MAX_POINT_LIGHTS 4

struct DirectionalLight
{
    vec3 Direction;
    vec3 Color;
    float SpecularStrength;
};

struct PointLight
{
	vec3 Position;
	vec3 Color;
	float SpecularStrength;
};

in vec2 FragTexcoord;
in vec3 FragNormal;
in vec3 FragPos;

uniform sampler2D Texture0;
uniform samplerCube Texture_Skybox;

uniform float AmbientStrength		= 0.15f;
uniform vec3 AmbientColor			= vec3(1.0f, 1.0f, 1.0f);

uniform PointLight PointLightArray[MAX_POINT_LIGHTS];
uniform unsigned int PointLightCount;

uniform vec3 CameraPos;
uniform float ObjectShininess		= 32.0f;

// Out
out vec4 FinalColor;

vec3 CalculateLight_Point(unsigned int index)
{
    PointLight light = PointLightArray[index];
    
    // Light direction
    vec3 lightDir = normalize(light.Position - FragPos);
    
    // Diffuse shading
    float diff = max(dot(FragNormal, lightDir), 0.0);
    vec3 diffuse = diff * light.Color;
    
    // Specular shading
    vec3 viewDir = normalize(FragPos - CameraPos);
    vec3 reflectDir = reflect(-lightDir, FragNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ObjectShininess);
    vec3 specular = spec * light.SpecularStrength * light.Color;
    
    // Combine results
    vec3 result = diffuse + specular;
    return result;
}

void main()
{
    // Ambient Component
    vec3 Ambient = AmbientStrength * AmbientColor;

    vec3 TotalLightOutput = vec3(0.0f);
    for (unsigned int i = 0; i < PointLightCount; ++i)
    {
        TotalLightOutput += CalculateLight_Point(i);
    }
    TotalLightOutput += Ambient;

    vec3 Normal = normalize(FragNormal);
    vec3 ViewDir = normalize(FragPos - CameraPos);
    vec3 ReflectDir = reflect(ViewDir, Normal);

    // Calculate the final color
    vec4 ObjectTexture = texture(Texture0, FragTexcoord);
    vec4 ReflectionTexture = texture(Texture_Skybox, ReflectDir);
    vec4 MixedTexture = mix(ObjectTexture, ReflectionTexture, 0.5f);
    FinalColor = vec4(TotalLightOutput, 1.0f) * MixedTexture;
}