#version 460 core

layout (column_major) uniform UniformData
{
    mat4 world;
    mat4 view;
    mat4 projection;
    float currentTime;
};

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 texCoord;


void main(void)
{
    gl_Position = projection * view * world * vec4(vertexPosition, 1.0);

    outColor = vec3(vertexTexCoords.x,vertexTexCoords.y,0); // pass the texture coordinates to fragment shader
}
