#version 460 core

layout(location = 0) in vec2 outTexcoord;

layout(location = 0) out vec4 color;

uniform sampler2D tex1;

void main()
{
	vec4 texColor = texture(tex1, outTexcoord);
	color = vec4(texColor.rgb,1.0);
}
