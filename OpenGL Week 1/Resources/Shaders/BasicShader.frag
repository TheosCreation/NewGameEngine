#version 460 core

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec4 outColor;


uniform sampler2D texture1;



void main(){

   float borderThickness = 0.03;

   //if texcoords are in the border thickness area, let's return a light blue color (0,0.5,1,1), otherwise, let's make a faded color
   if ((inColor.x > 0.0+borderThickness && inColor.x < 1.0-borderThickness) && (inColor.y > 0.0+borderThickness && inColor.y < 1.0-borderThickness))
       outColor = vec4(0,0,0.2+inColor.x,1);
   else
       outColor = vec4(0,0.5,1,1);
       
       
  vec4 texColor = texture(texture1, texCoord);

  outColor = texColor;
  
}
