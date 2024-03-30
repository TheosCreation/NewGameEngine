#version 460 core

uniform float currentTime;

layout(location = 0) in vec2 texCoord;

out vec4 color;

uniform sampler2D texture1;

void main(){
	float animSpeed = 10.0f;
	float roundedTime = round(currentTime * animSpeed);

	vec2 newTexCoord = vec2(texCoord.x + (0.1 * roundedTime), texCoord.y);
	vec4 texColor = texture(texture1, newTexCoord);

	color = texColor;
}
