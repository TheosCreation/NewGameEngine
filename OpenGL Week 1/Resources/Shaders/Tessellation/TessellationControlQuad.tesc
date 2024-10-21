#version 460 core

layout (vertices = 3) out;

void main()
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelOuter[0] = 5.0;
        gl_TessLevelOuter[1] = 5.0;
        gl_TessLevelOuter[2] = 5.0;

        gl_TessLevelInner[0] = 3.0;
    }

    // Pass through input positions to output without any changes.
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}