#version 150
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 pos[3];
in vec3 normal[3];
in vec2 st[3];
out vec3 posG;
out vec3 NormalG;
out vec2 stG;
void main()
{
	//Check if the triangel has normal otherwise calculate them
	vec3 Normal;
	if(dot(normal[0].xyz,vec3(1.0))<0.1)
	{
		vec3 LV = pos[1]-pos[0];
		vec3 RV = pos[2]-pos[0];
		//Take the cross product between the edges to find the normal
		Normal = normalize(cross(LV,RV));
	}else{
		Normal = normal[0];
	}

	

	//Send to the fragment shader
	for(int i = 0; i < gl_in.length(); i++)
	{
	 	gl_Position = gl_in[i].gl_Position;
	 	NormalG = Normal;
	 	posG = pos[i];
	 	stG = st[i];
	 	EmitVertex();
	}
	EndPrimitive();
}