
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

vec3 CalculateLight(Light baseLight, vec3 lightDir, vec3 viewDir, vec3 normal, float attenuation, float objectShininess)
{
    // Diffuse shading
    float DiffuseStrength = max(dot(normal, -lightDir), 0.0);
    vec3 Diffuse = DiffuseStrength * baseLight.Color;

    // Specular shading
    vec3 HalfwayDir = normalize(lightDir - viewDir);
    float SpecularReflection = pow(max(dot(normal, HalfwayDir), 0.0), objectShininess);
    vec3 Specular = baseLight.SpecularStrength * SpecularReflection * baseLight.Color;

    // Combine results
    vec3 result = (Diffuse + Specular) / attenuation;
    return result;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 viewDir, float objectShininess, vec3 fragNormal)
{
    vec3 LightDir = normalize(light.Direction);
    return CalculateLight(light.Base, LightDir, viewDir, fragNormal, 1.0, objectShininess);
}

vec3 CalculatePointLight(PointLight light, vec3 viewDir, float objectShininess, vec3 fragNormal, vec3 fragPos)
{
    vec3 LightDir = normalize(fragPos - light.Position);
    float Distance = length(light.Position - fragPos);
    float Attenuation = light.AttenuationConstant + (light.AttenuationLinear * Distance) + (light.AttenuationExponent * Distance * Distance);
    return CalculateLight(light.Base, LightDir, viewDir, fragNormal, Attenuation, objectShininess);
}

vec3 CalculateSpotLight(SpotLight light, vec3 viewDir, float objectShininess, vec3 fragNormal, vec3 fragPos)
{
    vec3 LightDir = normalize(fragPos - light.Position);
    float theta = dot(LightDir, normalize(light.Direction));
    float epsilon   = light.CutOff - light.OuterCutOff;
    float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0.0, 1.0);  
    float Distance = length(light.Position - fragPos);
    float Attenuation = light.AttenuationConstant + (light.AttenuationLinear * Distance) + (light.AttenuationExponent * Distance * Distance);
    return CalculateLight(light.Base, LightDir, viewDir, fragNormal, Attenuation, objectShininess) * intensity;
}