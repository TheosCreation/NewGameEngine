#version 460 core

//layout(binding = 0) uniform Data
layout (row_major) uniform UniformData //uniform buffer Data
{
    mat4 world;
    mat4 view;
    mat4 projection;
}; 


layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoords;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 texCoord;


void main(void)
{
    vec4 pos = vec4(vertexPosition, 1) * world; //multiply the world matrix with the vertex position in order to obtain the final position
    pos = pos * view ; //multiply the view matrix with the world position in order to obtain the position in view space
    pos = pos * projection; //multiply the projection matrix with the view position in order to obtain the final position in screen space

    gl_Position = pos;

    outColor = vec3(vertexTexCoords.x,vertexTexCoords.y,0); // pass the texture coordinates to fragment shader
    texCoord = vertexTexCoords;


}
