#version 460 core

uniform float currentTime;

in vec3 FragColor;

out vec4 color;

void main(){
    vec3 nextColor = vec3(FragColor.z,FragColor.x, FragColor.y);

    vec3 mixedColors = mix(FragColor, nextColor, (sin(currentTime) + 1.0) * 0.5);
    color = vec4(mixedColors, 1.0);
}
