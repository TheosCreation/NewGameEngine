#version 460 core

layout(location = 0) in vec3 inColor;

layout(location = 0) out vec4 outColor;


uniform sampler2D texture1;



void main() {

	vec4 texColor = texture(texture1, outTexcoord);

	outColor = texColor;
}
