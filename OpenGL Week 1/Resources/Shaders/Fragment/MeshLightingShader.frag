#version 460 core
#define MAX_POINT_LIGHTS 4
#include "Shadows.glsl"
#include "Lighting.glsl"

in vec2 FragTexcoord;

layout(binding = 0) uniform sampler2D Texture_Position;
layout(binding = 1) uniform sampler2D Texture_Normal;
layout(binding = 2) uniform sampler2D Texture_AlbedoShininess;
//layout(binding = 5) uniform sampler2D Texture_ShadowMap;

uniform float AmbientStrength = 0.15f;
uniform vec3 AmbientColor = vec3(1.0f, 1.0f, 1.0f);

uniform PointLight PointLightArray[MAX_POINT_LIGHTS];
uniform uint PointLightCount;

uniform DirectionalLight DirLight;
uniform int DirectionalLightStatus;

uniform SpotLight SpotLight1;
uniform int SpotLightStatus;

uniform vec3 CameraPos;
//uniform float ObjectShininess = 32.0f;

// Out
out vec4 FinalColor;

void main()
{
    // Normalize the normal and calculate view and reflection directions
    vec3 FragPos = texture(Texture_Position, FragTexcoord).rgb;
    vec3 FragNormal = texture(Texture_Normal, FragTexcoord).rgb;
    vec3 Albedo = texture(Texture_AlbedoShininess, FragTexcoord).rgb;
    float ObjectShininess = texture(Texture_AlbedoShininess, FragTexcoord).a;
    
    vec3 Normal = normalize(FragNormal);
    vec3 ViewDir = normalize(FragPos - CameraPos);
    vec3 ReflectDir = reflect(ViewDir, Normal);

    // Ambient Component
    vec3 Ambient = Albedo * AmbientStrength;

    // Calculate lighting
    vec3 TotalLightOutput = vec3(0.0);
    for (uint i = 0; i < PointLightCount; ++i)
    {
        TotalLightOutput += CalculatePointLight(PointLightArray[i], ViewDir, ObjectShininess, FragNormal, FragPos);
    }

    if (DirectionalLightStatus == 1)
    {
        TotalLightOutput += CalculateDirectionalLight(DirLight, ViewDir, ObjectShininess, FragNormal);
    }

    if (SpotLightStatus == 1)
    {
        TotalLightOutput += CalculateSpotLight(SpotLight1, ViewDir, ObjectShininess, FragNormal, FragPos);
    }
    
    //float Shadow = CalculateShadow(FragPos_LightSpace, Texture_ShadowMap);
    //vec3 LightShadow = Ambient + ((1.0f - Shadow) * TotalLightOutput);
    vec3 Lighting = Ambient + TotalLightOutput;

    // Calculate the final color
    FinalColor = vec4(Lighting, 1.0);
}