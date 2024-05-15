#version 460 core

in vec2 outTexcoord;

uniform sampler2D tex1;

out vec4 color;

void main()
{
	vec4 texColor = texture(tex1, outTexcoord);
	color = vec4(texColor.rgb,1.0);
}
