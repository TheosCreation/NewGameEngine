#version 460 core

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

out vec3 outColor;
out vec2 texCoord;   


void main(void)
{
    gl_Position = projection * view * world * vec4(vertexPosition, 1.0);

    outColor = vec3(vertexTexCoords.x,vertexTexCoords.y,0); // pass the texture coordinates to fragment shader
    texCoord = vertexTexCoords;


}
