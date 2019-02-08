#version 330 core
layout (location = 0) in vec3 Position;   // the position variable has attribute position 0
layout (location = 1) in vec3 Normal; 
layout (location = 2) in vec2 TextureCoords; 
  
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
void main()
{
	vec3 spos = Position;
  	gl_Position = projection*view*model*vec4(spos, 1.0);
}  