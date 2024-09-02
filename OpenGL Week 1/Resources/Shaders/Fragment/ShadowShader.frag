#version 460 core

in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragTexcoord;
in vec4 FragPosLightSpace; // Position in light space

uniform sampler2D shadowMap; // The shadow map

out vec4 FragColor;

float calculateShadow(vec4 fragPosLightSpace)
{
    // Transform to [0, 1] range
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Retrieve depth of the fragment in light space
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;

    // Check for shadow
    float shadow = currentDepth > closestDepth + 0.005 ? 1.0 : 0.0; // Simple shadow calculation
    return shadow;
}

void main()
{
    // Compute shadows
    float shadow = calculateShadow(FragPosLightSpace);

    // Combine with other lighting effects
    FragColor = vec4(1,1,1, 1.0);
}