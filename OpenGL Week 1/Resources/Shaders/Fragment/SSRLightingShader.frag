#version 460 core
#define MAX_POINT_LIGHTS 4
#include "Shadows.glsl"
#include "Lighting.glsl"

in vec2 FragTexcoord;

uniform sampler2D Texture_Position;     // G-buffer: Fragment position
uniform sampler2D Texture_Normal;       // G-buffer: Fragment normal
uniform sampler2D Texture_AlbedoShininess; // G-buffer: Albedo and shininess
uniform sampler2D Texture_ShadowMap;

uniform float AmbientStrength = 0.15f;
uniform vec3 AmbientColor = vec3(1.0f, 1.0f, 1.0f);

uniform PointLight PointLightArray[MAX_POINT_LIGHTS];
uniform uint PointLightCount;

uniform DirectionalLight DirLight;
uniform int DirectionalLightStatus;

uniform SpotLight SpotLight1;
uniform int SpotLightStatus;
// Light parameters
uniform vec3 CameraPos;
uniform mat4 VPLight;

// Output
out vec4 FinalColor;

void main()
{
    // Sample textures
    vec3 FragPos = texture(Texture_Position, FragTexcoord).xyz;
    vec3 FragNormal = texture(Texture_Normal, FragTexcoord).xyz;
    vec3 FragAlbedo = texture(Texture_AlbedoShininess, FragTexcoord).rgb;
    float ObjectShininess = texture(Texture_AlbedoShininess, FragTexcoord).a;
    
    vec3 ViewDir = normalize(FragPos - CameraPos);
    //vec3 ReflectDir = reflect(ViewDir, FragNormal);

    // Ambient Component
    vec3 Ambient = FragAlbedo * AmbientStrength;

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
    
    //vec4 FragPos_LightSpace = VPLight * vec4(FragPos, 1.0f);

    //float Shadow = CalculateShadow(FragPos_LightSpace, Texture_ShadowMap);
    //vec3 LightShadow = Ambient + ((1.0f - Shadow) * TotalLightOutput);
    vec3 Lighting = Ambient + TotalLightOutput;

    // Combine the results
    //vec3 Color = FragAlbedo;

    // Output final color
    FinalColor = vec4(Lighting, 1.0);
}
