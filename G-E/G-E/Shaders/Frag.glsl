
#version 330 core
out vec4 FragColor;  
in vec3 posG;  
in vec3 NormalG;
in vec2 stG;
in vec3 VG;
void main()
{

	//Define here should be i cpu
	vec3 LightPos =vec3(0.0,0.0,1.0);
	vec3 lightColor= vec3(1.0,1.0,1.0);
	vec3 Color = vec3(1.0,0.5,0.0);
	





	//Ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength*lightColor;


	//Diffuse
	vec3 norm =normalize(NormalG);
	vec3 lightdir = normalize(LightPos-posG);
	float diff = max(dot(norm,lightdir), 0.0);
	vec3 diffuse = diff* lightColor;

	//Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(VG - posG);
	vec3 reflectDir = reflect(-lightdir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	vec3 result = (ambient+diffuse+specular)*Color;


	FragColor = vec4(result,1.0);
}