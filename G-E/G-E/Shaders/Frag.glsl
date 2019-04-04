
#version 330 core
out vec4 FragColor;  
in vec3 posG;  
in vec3 NormalG;
in vec2 stG;
in vec3 VG;

//Directional Light
struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

//Point Light
struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool init;
};

#define NR_POINT_LIGHTS 4
#define NR_DIR_LIGHTS 1  
#define NR_SPOT_LIGHTS 4
//Uniforms
uniform DirLight dirLight[NR_DIR_LIGHTS];
uniform PointLight pointLights[NR_POINT_LIGHTS];

//Color of object
vec3 Color = vec3(1.0,0.5,0.0);
//Functions
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

	//Normalize and calulate viewdirection
	vec3 Normal = normalize(NormalG);
	vec3 viewDir =normalize(VG-posG);

	//Get directional light
	//vec3 result = CalcDirLight(dirLight[0],Normal,viewDir );
	vec3 result =vec3(0.0);

	//Get point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		//If light has been initialized
		if(pointLights[i].init)
		{
        	result += CalcPointLight(pointLights[i], Normal, posG, viewDir); 
		}
	}
		//Get point lights
	for(int i = 0; i < NR_DIR_LIGHTS; i++)
	{
	
       	result += CalcDirLight(dirLight[i], Normal, viewDir); 
	
	}
	//Assign color to pixel
	FragColor = vec4(result,1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // combine results
    vec3 ambient = light.ambient * Color;
    vec3 diffuse = light.diffuse * diff * Color;
    vec3 specular = light.specular * spec * Color;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * Color;
    vec3 diffuse = light.diffuse * diff * Color;
    vec3 specular = light.specular * spec * Color;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}