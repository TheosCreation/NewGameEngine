#version 460 core

in vec2 texCoord;

out vec4 color;

uniform sampler2D texture1;

void main(){
  vec4 texColor = texture(texture1, texCoord);

  color = texColor;
}
