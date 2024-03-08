#version 460 core


struct LightData
{
	vec4 color;
	vec4 direction;
};

layout (row_major) uniform UniformData
{
    mat4 world;
    mat4 view;
    mat4 projection;
    vec4 cameraPos;
    LightData lights[32];
    int lightsNum;
}; 


layout(location = 0) in vec2 outTexcoord;
layout(location = 1) in vec3 outNormal;
layout(location = 2) in vec3 outDirToCamera;

layout(location = 0) out vec4 color;

uniform sampler2D tex1;


vec3 computePhongDirLighting(float ka,vec3 ia,float kd,vec3 id,float ks,vec3 is,float shininess,
 vec3 color, vec3 normal,vec3 lightDir,vec3 dirToDCamera)
{
	//computing diffuse light
	float amount_diffuse_light = max(dot(lightDir, normal),0.0);
	//id *= (color.rgb);
	vec3 diffuse_light = kd * id * amount_diffuse_light;

	//computing specular light
	vec3 reflected_light = reflect(lightDir, normal);
	float amount_specular_light = pow(max(0.0, dot(reflected_light, dirToDCamera)), shininess);

	vec3 specular_light = ks * amount_specular_light * is;

	//computing light
	vec3 final_light = diffuse_light + specular_light;
	
	return final_light;
}


vec3 processLighting(vec3 color, vec3 normal, vec3 dirToDCamera)
{	
	vec3 final_light = vec3(0,0,0);

	//computing ambient light
	//hard-coded ambient light color based on the skybox environment map

	float ka = 0.4;
	vec3 ia = vec3(75.0/255.0,112.0/255.0,165.0/255.0);

	vec3 ambient_light = ka * ia;


	//sum the contribution of all the lights all together in one final result
	for (int i = 0; i< lightsNum;i++)
	{
		float kd = 1.0;
		vec3 id = lights[i].color.rgb;
		
		float ks = 1.0;
		vec3 is = vec3(1.0, 1.0, 1.0);
		
		float shininess = 30.0;

		final_light += computePhongDirLighting(ka,ia,kd,id,ks,is,shininess,color,normal, lights[i].direction.xyz, dirToDCamera);
	}


	//computing final lighting by adding the ambient light;
	return  ambient_light + final_light;
}





void main()
{
	vec4 texColor = texture(tex1, outTexcoord);
	vec3 final_light = vec3(0,0,0);
	final_light = processLighting(texColor.rgb,outNormal.xyz,outDirToCamera.xyz);
	color = vec4(final_light,1.0);
}