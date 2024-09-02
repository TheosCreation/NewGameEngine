#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 VPMatrix; // View * Projection matrix

uniform mat4 VPLight;

out vec2 FragTexcoord;
out vec3 FragNormal;
out vec3 FragPos;
out vec4 FragPosLightSpace; // Position in light space

void main()
{
    vec4 worldPos = modelMatrix * vec4(vertexPosition, 1.0f);
    gl_Position = VPMatrix * worldPos;
    FragTexcoord = vertexTexCoords;
    FragNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    FragPos = vec3(worldPos);
    FragPosLightSpace = VPLight * worldPos;
}