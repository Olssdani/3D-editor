#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
  
out vec3 pos;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform float Time;


void main()
{
	vec3 spos = aPos;
  gl_Position = projection*view*model*vec4(spos, 1.0);
	pos = vec4(spos, 1.0).xyz; 
}  