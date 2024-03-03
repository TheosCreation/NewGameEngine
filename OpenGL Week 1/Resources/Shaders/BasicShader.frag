#version 460 core

in vec3 FragColor;

out vec4 FinalColor;

void main()
{
	float borderThickness = 0.03;


	//if texcoords are in the border thickness area, let's return a light blue color (0,0.5,1,1), otherwise, let's make a faded color
   if ((FragColor.x > 0.0+borderThickness && FragColor.x < 1.0-borderThickness) && (FragColor.y > 0.0+borderThickness && FragColor.y < 1.0-borderThickness))
       FinalColor = vec4(0,0,0.2+FragColor.x,1);
   else
       FinalColor = vec4(0,0.5,1,1);

   FinalColor.a =1;
   FinalColor.rgb*=0.99;
}
