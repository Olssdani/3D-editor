
#version 330 core
out vec4 FragColor;  
in vec3 ourColorG;
in vec3 posG;  
in vec3 NormalG;
in vec2 stG;
void main()
{

	FragColor = vec4(abs(NormalG),1.0);
}