#version 460 core

layout (quads, equal_spacing, ccw) in;

uniform mat4 ModelMatrix;
uniform mat4 VPMatrix;

void main()
{
    vec4 Pos =  gl_TessCoord.x * gl_in[0].gl_Position +
                gl_TessCoord.y * gl_in[1].gl_Position +
                gl_TessCoord.z * gl_in[2].gl_Position;

    gl_Position = VPMatrix * ModelMatrix * Pos;
}