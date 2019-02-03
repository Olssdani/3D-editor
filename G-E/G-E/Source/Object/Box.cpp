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
	shader = new Shader("C:/Users/Daniel olsson/Documents/Programmering/G-E/G-E/G-E/Shaders/Vert.glsl", "C:/Users/Daniel olsson/Documents/Programmering/G-E/G-E/G-E/Shaders/Frag.glsl", "C:/Users/Daniel olsson/Documents/Programmering/G-E/G-E/G-E/Shaders/Geo.glsl");

}

void Box::CreateMesh()
{
	//Resize vector and set vertex position
	vertices.resize(8);
	vertices[0] = Vertex{ glm::vec3(xSize / 2, ySize / 2, zSize / 2) };
	vertices[1] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, zSize / 2) };
	vertices[2] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, zSize / 2) };
	vertices[3] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, zSize / 2) };
	vertices[4] = Vertex{ glm::vec3(xSize / 2, ySize / 2, -zSize / 2) };
	vertices[5] = Vertex{ glm::vec3(xSize / 2, -ySize / 2, -zSize / 2) };
	vertices[6] = Vertex{ glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2) };
	vertices[7] = Vertex{ glm::vec3(-xSize / 2, ySize / 2, -zSize / 2) };

	indices.resize(12 * 3);
	//top
	indices[0] = 0;
	indices[1] = 4;
	indices[2] = 7;

	indices[3] = 0;
	indices[4] = 7;
	indices[5] = 3;

	//front
	indices[6] = 0;
	indices[7] = 3;
	indices[8] = 1;

	indices[9] = 1;
	indices[10] = 3;
	indices[11] = 2;

	//bottom
	indices[12] = 1;
	indices[13] = 5;
	indices[14] = 6;

	indices[15] = 1;
	indices[16] = 2;
	indices[17] = 6;

	//Back
	indices[18] = 4;
	indices[19] = 5;
	indices[20] = 7;

	indices[21] = 5;
	indices[22] = 6;
	indices[23] = 7;

	//right
	indices[24] = 0;
	indices[25] = 1;
	indices[26] = 5;

	indices[27] = 0;
	indices[28] = 5;
	indices[29] = 4;

	//Left
	indices[30] = 3;
	indices[31] = 6;
	indices[32] = 2;

	indices[33] = 3;
	indices[34] = 7;
	indices[35] = 6;
}

Box::~Box()
{
	indices.clear();
	vertices.clear();
}
