#version 460 core

layout(location = 0) in vec2 texCoord;

layout(location = 0) out vec4 color;


uniform sampler2D texture1;



void main(){
  vec4 texColor = texture(texture1, texCoord);

  color = texColor;
}
