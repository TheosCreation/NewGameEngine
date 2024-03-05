#version 460 core

layout (row_major) uniform UniformData
{
    mat4 world;
	mat4 view;
	mat4 projection;
};

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoords;

layout (location = 0) out vec3 FragColor;
layout(location = 1) out vec2 texCoord;

void main(void)
{
	vec4 pos = vec4(vertexPosition, 1.0f) * world;
	pos = pos * view;
	pos = pos * projection;

	gl_Position = pos;

	FragColor = vec3(texcoord.x, texcoord.y, 0);
	texCoord = vertexTexCoords;
}