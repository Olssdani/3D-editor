
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

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

#define NR_POINT_LIGHTS 4
#define NR_DIR_LIGHTS 1  
#define NR_SPOT_LIGHTS 4
//Uniforms
uniform DirLight dirLight[NR_DIR_LIGHTS];
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform bool textureEnable;
uniform Material material;

//Functions
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform sampler2D ourTexture;
Material temp;
void main()
{
    if(textureEnable)
    {
        //Color = vec3(texture(ourTexture, stG));
    }else{

    }

    temp.ambient = vec3(0.0,1.0,0.0);
    temp.diffuse = vec3(0.0,1.0,0.0);
    temp.specular = vec3(0.0,1.0,0.0);
	//Normalize and calulate viewdirection
	vec3 Normal = normalize(NormalG);
	vec3 viewDir =normalize(VG-posG);

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
	// Add directional lights
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}