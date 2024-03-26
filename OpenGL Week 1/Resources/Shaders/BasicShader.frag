#version 460 core

in vec3 outColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D texture1;

void main(){

   float borderThickness = 0.03;

   //if texcoords are in the border thickness area, let's return a light blue color (0,0.5,1,1), otherwise, let's make a faded color
   if ((outColor.x > 0.0+borderThickness && outColor.x < 1.0-borderThickness) && (outColor.y > 0.0+borderThickness && outColor.y < 1.0-borderThickness))
       color = vec4(0,0,0.2+outColor.x,1);
   else
       color = vec4(0,0.5,1,1);
       
       
  vec4 texColor = texture(texture1, texCoord);

  //color.a =1;
  //color.rgb*=0.99;

  color = texColor;

  
}
