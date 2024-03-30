#version 460 core

uniform float currentTime;
uniform vec3 flowingColor;

in vec3 FragColor;

out vec4 color;

void main(){
    vec3 mixedColors = mix(FragColor, flowingColor, (sin(currentTime) + 1.0) * 0.5);

    color = vec4(mixedColors, 1.0);
}
