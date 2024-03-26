#version 460 core

in vec3 outColor;
in vec2 texCoord;

out vec4 color;



void main(){
    vec3 canvas = vec3(0.0);
    vec3 color_RED = vec3(1.0, 0.0, 0.0);
    vec3 color_BLUE = vec3(0.0, 0.0, 1.0);

    vec2 st = vec2(abs(sin(gl_FragCoord.x * 0.01)), 1);

    canvas = mix(color_RED, color_BLUE, st.x);

    color = vec4(canvas.x, canvas.y, canvas.z, 1.0);
}
