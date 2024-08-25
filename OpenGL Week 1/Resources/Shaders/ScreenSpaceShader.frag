#version 460 core

in vec2 FragTexcoord;

uniform sampler2D Texture0;
uniform vec3 uColor;

// Output
out vec4 FinalColor;

void main()
{
    vec4 texColor = texture(Texture0, FragTexcoord);

    // Check if the texture is "null" (completely transparent)
    if (texColor.a == 0.0)
    {
        // Use uColor if texture is "null"
        FinalColor = vec4(uColor, 1.0);
    }
    else
    {
        // Use the texture color
        FinalColor = texColor;
    }
}