#version 460 core
#define MAX_POINT_LIGHTS 4
#include "Shadows.glsl"
#include "Lighting.glsl"

in vec3 FragPos;
in vec2 FragTexcoord;
in vec3 FragNormal;
in vec4 FragPos_LightSpace;

uniform sampler2D Texture0;
uniform samplerCube Texture_Skybox;
uniform sampler2D ReflectionMap;
uniform sampler2D Texture_ShadowMap;

uniform float AmbientStrength = 0.15f;
uniform vec3 AmbientColor = vec3(1.0f, 1.0f, 1.0f);

uniform PointLight PointLightArray[MAX_POINT_LIGHTS];
uniform uint PointLightCount;

uniform DirectionalLight DirLight;
uniform int DirectionalLightStatus;

uniform SpotLight SpotLight1;
uniform int SpotLightStatus;

uniform vec3 CameraPos;
uniform float ObjectShininess = 32.0f;

// Out
out vec4 FinalColor;

void main()
{
    // Normalize the normal and calculate view and reflection directions
    vec3 Normal = normalize(FragNormal);
    vec3 ViewDir = normalize(FragPos - CameraPos);
    vec3 ReflectDir = reflect(ViewDir, Normal);

    // Ambient Component
    vec3 Ambient = AmbientStrength * AmbientColor;

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
    
    float Shadow = CalculateShadow(FragPos_LightSpace, Texture_ShadowMap);
    vec3 LightShadow = Ambient + ((1.0f - Shadow) * TotalLightOutput);

    // Sample textures
    vec4 ObjectTexture = texture(Texture0, FragTexcoord);
    vec4 ReflectionTexture = texture(Texture_Skybox, ReflectDir);
    float Reflectivity = texture(ReflectionMap, FragTexcoord).r; // Sample the red channel of the reflection map

    // Mix object texture and reflection texture based on reflectivity
    vec4 MixedTexture = mix(ObjectTexture, ReflectionTexture, Reflectivity);

    // Calculate the final color
    FinalColor = vec4(LightShadow, 1.0) * MixedTexture;
}