#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in mat4 InstancedModel;

uniform mat4 mvpMatrix;
uniform mat4 VPMatrix;

out vec2 FragTexcoord;
out vec3 FragNormal;
out vec3 FragPos;

void main(void)
{
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0f);
    //gl_Position = VPMatrix * InstancedModel * vec4(vertexPosition, 1.0f);
    FragTexcoord = vertexTexCoords;
    FragNormal = mat3(transpose(inverse(InstancedModel))) * vertexNormal;
    FragPos = vec3(InstancedModel * vec4(vertexPosition, 1.0f));
}
