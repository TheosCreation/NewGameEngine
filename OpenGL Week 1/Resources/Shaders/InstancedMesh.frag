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

    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
};

in vec2 FragTexcoord;
in vec3 FragNormal;
in vec3 FragPos;

uniform sampler2D Texture0;
uniform samplerCube Texture_Skybox;
uniform sampler2D ReflectionMap;

uniform float AmbientStrength = 0.15f;
uniform vec3 AmbientColor = vec3(1.0f, 1.0f, 1.0f);

uniform PointLight PointLightArray[MAX_POINT_LIGHTS];
uniform unsigned int PointLightCount;

uniform DirectionalLight DirLight;
uniform int DirectionalLightStatus;

uniform vec3 CameraPos;
uniform float ObjectShininess = 32.0f;

// Out
out vec4 FinalColor;

vec3 CalculateLight_Point(unsigned int index, vec3 viewDir)
{
    vec3 Normal = normalize(FragNormal);
    PointLight light = PointLightArray[index];

    // Light direction
    vec3 LightDir = normalize(FragPos - light.Position);

    // Diffuse shading
    float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
    vec3 Diffuse = DiffuseStrength * light.Color;

    // Specular shading
    vec3 HalfwayDir = normalize(LightDir + viewDir);
    float SpecularReflection = pow(max(dot(Normal, HalfwayDir), 0.0), ObjectShininess);
    vec3 Specular = light.SpecularStrength * SpecularReflection * light.Color;

    // Combine results
    vec3 result = Diffuse + Specular;

    float Distance = length(light.Position - FragPos);
    float Attenuation = light.AttenuationConstant + (light.AttenuationLinear * Distance) + (light.AttenuationExponent * pow(Distance, 2));
    return result /= Attenuation;
}

vec3 CalculateLight_Directional(vec3 viewDir)
{
    vec3 Normal = normalize(FragNormal);

    // Light direction
    vec3 LightDir = normalize(-DirLight.Direction);

    // Diffuse shading
    float DiffuseStrength = max(dot(Normal, -LightDir), 0.0f);
    vec3 Diffuse = DiffuseStrength * DirLight.Color;

    // Specular shading
    vec3 halfwayDir = normalize(LightDir + viewDir);
    float SpecularStrength = pow(max(dot(Normal, halfwayDir), 0.0), ObjectShininess);
    vec3 Specular = SpecularStrength * DirLight.Color;

    // Combine results
    vec3 result = Diffuse + Specular;
    return result;
}

void main()
{
    // Normalize the normal and calculate view and reflection directions
    vec3 Normal = normalize(FragNormal);
    vec3 ViewDir = normalize(CameraPos - FragPos);
    vec3 ReflectDir = reflect(ViewDir, Normal);

    // Ambient Component
    vec3 Ambient = AmbientStrength * AmbientColor;

    vec3 TotalLightOutput = vec3(0.0f);
    for (unsigned int i = 0; i < PointLightCount; ++i)
    {
        TotalLightOutput += CalculateLight_Point(i, ViewDir);
    }

    // if the directional light is turned off it will not calculate the directional light
    if(DirectionalLightStatus == 1)
    {
        TotalLightOutput += CalculateLight_Directional(ViewDir);
    }

    TotalLightOutput += Ambient;

    // Sample textures
    vec4 ObjectTexture = texture(Texture0, FragTexcoord);
    vec4 ReflectionTexture = texture(Texture_Skybox, ReflectDir);
    float Reflectivity = texture(ReflectionMap, FragTexcoord).r; // Sample the red channel of the reflection map

    // Mix object texture and reflection texture based on reflectivity
    vec4 MixedTexture = mix(ObjectTexture, ReflectionTexture, Reflectivity);

    // Calculate the final color
    FinalColor = vec4(TotalLightOutput, 1.0f) * MixedTexture;
}