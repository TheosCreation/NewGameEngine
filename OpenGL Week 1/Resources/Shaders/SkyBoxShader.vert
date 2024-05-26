#version 460 core

layout(location = 0) in vec3 Position;

uniform mat4 VPMatrix;

out vec3 FragTexcoord;

void main()
{
    gl_Position = VPMatrix * vec4(Position, 1.0f);
    FragTexcoord = Position.xyz;
}