#include "Box.h"



Box::Box(float _xSize, float _ySize, float _zSize)
{
	//Set variavle
	xSize = _xSize;
	ySize = _ySize;
	zSize = _zSize;
	//Create mesh
	CreateMesh();
	//Connect mesh to buffers
	Object::CreateBuffers(vertices, indices);

	DrawSize = indices.size();
	//Clear unessary data
	vertices.clear();
	indices.clear();
	//Set standard shader
	shader = new Shader("Shaders/Vert.glsl", "Shaders/Frag.glsl", "Shaders/Geo.glsl");
	Object::material = new Material(shader);

}

void Box::CreateMesh()
{
	//Resize vector and set vertex position
	vertices.resize(24);
	//FRONT, RIGHT, UP
	vertices[0] = Vertex{ glm::vec3(xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0,0.0,1.0), glm::vec2(1.0,1.0) };
	vertices[1] = Vertex{ glm::vec3(xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0,1.0,0.0),glm::vec2(1.0,0.0) };
	vertices[2] = Vertex{ glm::vec3(xSize / 2, ySize / 2, zSize / 2), glm::vec3(1.0,0.0,0.0),glm::vec2(0.0,1.0) };
	//FRONT, RIGHT, DOWN
	vertices[3] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, zSize / 2) , glm::vec3(0.0,0.0,1.0), glm::vec2(1.0,0.0) };
	vertices[4] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, zSize / 2) , glm::vec3(0.0,-1.0,0.0), glm::vec2(1.0,1.0) };
	vertices[5] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, zSize / 2) , glm::vec3(1.0,0.0,0.0), glm::vec2(0.0,0.0) };
	//FRONT, LEFT, DOWN
	vertices[6] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, zSize / 2), glm::vec3(0.0,0.0,1.0), glm::vec2(0.0,0.0) };
	vertices[7] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, zSize / 2), glm::vec3(0.0,-1.0,0.0), glm::vec2(0.0,1.0) };
	vertices[8] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, zSize / 2), glm::vec3(-1.0,0.0,0.0), glm::vec2(1.0,0.0) };

	//FRONT, LEFT, UP
	vertices[9] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0,0.0,1.0), glm::vec2(0.0,1.0) };
	vertices[10] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0,1.0,0.0), glm::vec2(0.0,0.0) };
	vertices[11] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, zSize / 2), glm::vec3(-1.0,0.0,0.0), glm::vec2(1.0,1.0) };

	//BACK, LEFT, UP
	vertices[12] = Vertex{ glm::vec3(xSize / 2, ySize / 2, -zSize / 2), glm::vec3(0.0,0.0,-1.0), glm::vec2(0.0,1.0) };
	vertices[13] = Vertex{ glm::vec3(xSize / 2, ySize / 2, -zSize / 2), glm::vec3(0.0,1.0,0.0), glm::vec2(1.0,1.0) };
	vertices[14] = Vertex{ glm::vec3(xSize / 2, ySize / 2, -zSize / 2), glm::vec3(1.0,0.0,0.0), glm::vec2(1.0,1.0) };

	//BACK, LEFT, DOWN
	vertices[15] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, -zSize / 2), glm::vec3(0.0,0.0,-1.0), glm::vec2(0.0,0.0) };
	vertices[16] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, -zSize / 2), glm::vec3(0.0,-1.0,0.0), glm::vec2(1.0,0.0) };
	vertices[17] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, -zSize / 2), glm::vec3(1.0,0.0,0.0), glm::vec2(1.0,0.0) };

	//BACK, RIGHT, DOWN
	vertices[18] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2) , glm::vec3(0.0,0.0,-1.0), glm::vec2(1.0,0.0) };
	vertices[19] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2) , glm::vec3(0.0,-1.0,0.0), glm::vec2(0.0,0.0) };
	vertices[20] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2) , glm::vec3(-1.0,0.0,0.0), glm::vec2(0.0,0.0) };

	//BACK, RIGHT, UP
	vertices[21] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, -zSize / 2) , glm::vec3(0.0,0.0,-1.0), glm::vec2(1.0,1.0) };
	vertices[22] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, -zSize / 2) , glm::vec3(0.0,1.0,0.0), glm::vec2(0.0,1.0) };
	vertices[23] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, -zSize / 2) , glm::vec3(-1.0,0.0,0.0), glm::vec2(0.0,1.0) };

	indices.resize(12 * 3);
	//top
	indices[0] = 1;
	indices[1] = 13;
	indices[2] = 22;

	indices[3] = 1;
	indices[4] = 22;
	indices[5] = 10;

	//front
	indices[6] = 0;
	indices[7] = 9;
	indices[8] = 3;

	indices[9] = 9;
	indices[10] =6;
	indices[11] =3;

	//bottom
	indices[12] = 4;
	indices[13] = 7;
	indices[14] = 16;

	indices[15] = 7;
	indices[16] = 19;
	indices[17] = 16;

	//Back
	indices[18] = 12;
	indices[19] = 15;
	indices[20] = 18;

	indices[21] = 12;
	indices[22] = 18;
	indices[23] = 21;

	//right
	indices[24] = 2;
	indices[25] = 5;
	indices[26] = 17;

	indices[27] = 2;
	indices[28] = 17;
	indices[29] = 14;

	//Left
	indices[30] = 8;
	indices[31] = 11;
	indices[32] = 23;

	indices[33] = 8;
	indices[34] = 23;
	indices[35] = 20;
}

Box::~Box()
{
	delete material;
	indices.clear();
	vertices.clear();
}
