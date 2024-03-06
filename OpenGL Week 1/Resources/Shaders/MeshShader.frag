#version 460 core

layout(location = 0) in vec2 outTexcoord;

layout(location = 0) out vec4 color;


uniform sampler2D tex;



void main(){
  vec4 texColor = texture(tex, outTexcoord);

  color = texColor;
}
