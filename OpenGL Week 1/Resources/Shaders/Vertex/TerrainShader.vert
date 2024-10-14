#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 modelMatrix;
uniform mat4 VPMatrix;

uniform mat4 VPLight;

out vec2 FragTexcoord;
out vec3 FragNormal;
out vec3 FragPos;
out float Height;
out vec4 FragPos_LightSpace;

void main()
{
    gl_Position = VPMatrix * modelMatrix * vec4(vertexPosition, 1.0f);
    FragTexcoord = vertexTexCoords;
    FragNormal = mat3(transpose(inverse(modelMatrix))) * vertexNormal;
    FragPos = vec3(modelMatrix * vec4(vertexPosition, 1.0f));
    Height = vertexPosition.y;

    FragPos_LightSpace = VPLight * vec4(FragPos, 1.0f);
}