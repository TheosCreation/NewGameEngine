#version 460 core
#define MAX_POINT_LIGHTS 4

struct Light {
    vec3 Color;
    float SpecularStrength;
};

struct DirectionalLight {
    Light Base;
    vec3 Direction;
};

struct PointLight {
    Light Base;
    vec3 Position;
    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
};

struct SpotLight {
    Light Base;
    vec3 Position;
    vec3 Direction;
    float CutOff;
    float OuterCutOff;
    float AttenuationConstant;
    float AttenuationLinear;
    float AttenuationExponent;
};

in vec3 FragPos;
in vec2 FragTexcoord;
in vec3 FragNormal;

uniform sampler2D Texture0;
uniform samplerCube Texture_Skybox;
uniform sampler2D ReflectionMap;

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

vec3 CalculateLight(Light baseLight, vec3 lightDir, vec3 viewDir, vec3 normal, float attenuation)
{
    // Diffuse shading
    float DiffuseStrength = max(dot(normal, -lightDir), 0.0);
    vec3 Diffuse = DiffuseStrength * baseLight.Color;

    // Specular shading
    vec3 HalfwayDir = normalize(lightDir - viewDir);
    float SpecularReflection = pow(max(dot(normal, HalfwayDir), 0.0), ObjectShininess);
    vec3 Specular = baseLight.SpecularStrength * SpecularReflection * baseLight.Color;

    // Combine results
    vec3 result = (Diffuse + Specular) / attenuation;
    return result;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 viewDir)
{
    vec3 LightDir = normalize(light.Direction);
    return CalculateLight(light.Base, LightDir, viewDir, normalize(FragNormal), 1.0);
}

vec3 CalculatePointLight(PointLight light, vec3 viewDir)
{
    vec3 LightDir = normalize(FragPos - light.Position);
    float Distance = length(light.Position - FragPos);
    float Attenuation = light.AttenuationConstant + (light.AttenuationLinear * Distance) + (light.AttenuationExponent * Distance * Distance);
    return CalculateLight(light.Base, LightDir, viewDir, normalize(FragNormal), Attenuation);
}

vec3 CalculateSpotLight(SpotLight light, vec3 viewDir)
{
    vec3 LightDir = normalize(FragPos - light.Position);
    float theta = dot(LightDir, normalize(light.Direction));
    float epsilon   = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);  
    float Distance = length(light.Position - FragPos);
    float Attenuation = light.AttenuationConstant + (light.AttenuationLinear * Distance) + (light.AttenuationExponent * Distance * Distance);
    return CalculateLight(light.Base, LightDir, viewDir, normalize(FragNormal), Attenuation) * intensity;
}

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
        TotalLightOutput += CalculatePointLight(PointLightArray[i], ViewDir);
    }

    if (DirectionalLightStatus == 1)
    {
        TotalLightOutput += CalculateDirectionalLight(DirLight, ViewDir);
    }

    if (SpotLightStatus == 1)
    {
        TotalLightOutput += CalculateSpotLight(SpotLight1, ViewDir);
    }

    TotalLightOutput += Ambient;

    // Sample textures
    vec4 ObjectTexture = texture(Texture0, FragTexcoord);
    vec4 ReflectionTexture = texture(Texture_Skybox, ReflectDir);
    float Reflectivity = texture(ReflectionMap, FragTexcoord).r; // Sample the red channel of the reflection map

    // Mix object texture and reflection texture based on reflectivity
    vec4 MixedTexture = mix(ObjectTexture, ReflectionTexture, Reflectivity);

    // Calculate the final color
    FinalColor = vec4(TotalLightOutput, 1.0) * MixedTexture;
}