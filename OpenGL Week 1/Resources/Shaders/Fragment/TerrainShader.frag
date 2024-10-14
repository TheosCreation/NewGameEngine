#version 460 core
#define MAX_POINT_LIGHTS 4
#include "Shadows.glsl"
#include "Lighting.glsl"

in vec3 FragPos;
in vec2 FragTexcoord;
in vec3 FragNormal;
in float Height;
in vec4 FragPos_LightSpace;

layout(binding = 0) uniform sampler2D Texture0; // Base texture
layout(binding = 1) uniform sampler2D Texture1; // Additional texture
layout(binding = 2) uniform sampler2D Texture2; // Additional texture
layout(binding = 3) uniform sampler2D Texture3; // Additional texture
layout(binding = 4) uniform sampler2D HeightMap; // Height map for blending
layout(binding = 5) uniform sampler2D Texture_ShadowMap;

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

const float lowerHeight = 30;
const float lowerMiddleHeight = 60;
const float upperMiddleHeight = 90;
const float upperHeight = 120;

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
    
    float Shadow = CalculateShadow(FragPos_LightSpace, Texture_ShadowMap);
    vec3 LightShadow = Ambient + ((1.0f - Shadow) * TotalLightOutput);

    // Sample textures
    vec4 BaseTexture = texture(Texture0, FragTexcoord);
    vec4 AdditionalTexture1 = texture(Texture1, FragTexcoord); // Additional texture for blending
    vec4 AdditionalTexture2 = texture(Texture2, FragTexcoord);
    vec4 AdditionalTexture3 = texture(Texture3, FragTexcoord);

    float blendGrass = 1.0 - smoothstep(lowerHeight, lowerMiddleHeight, Height);
    float blendDirt = smoothstep(lowerHeight, lowerMiddleHeight, Height) * (1.0 - smoothstep(lowerMiddleHeight, upperMiddleHeight, Height));
    float blendStone = smoothstep(lowerMiddleHeight, upperMiddleHeight, Height) * (1.0 - smoothstep(upperMiddleHeight, upperHeight, Height));
    float blendSnow = smoothstep(upperMiddleHeight, upperHeight, Height);
    
    vec4 BlendedTexture = BaseTexture * blendGrass + AdditionalTexture1 * blendDirt + AdditionalTexture2 * blendStone + AdditionalTexture3 * blendSnow;

    // Calculate the final color
    FinalColor = vec4(LightShadow, 1.0) * BlendedTexture;
}