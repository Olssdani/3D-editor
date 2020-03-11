#include "Box.h"

Box::Box(float _xSize, float _ySize, float _zSize) {
	//Set variavle
	xSize = _xSize;
	ySize = _ySize;
	zSize = _zSize;
	//Create mesh
	CreateMesh();
	//Connect mesh to buffers
	object::CreateBuffers(vertices, indices);

	drawSize = indices.size();
	//Clear unessary data
	vertices.clear();
	indices.clear();
	//Set standard shader
	SetShader("Shaders/Vert.glsl", "Shaders/Frag.glsl", "Shaders/Geo.glsl");
	object::material = new Material(shader);
}

void Box::CreateMesh() {
	//Resize vector and set vertex position
	vertices.resize(24);
	//FRONT, RIGHT, UP
	vertices[0] = vertex{
		glm::vec3(xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 1.0)};
	vertices[1] = vertex{
		glm::vec3(xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 0.0)};
	vertices[2] = vertex{
		glm::vec3(xSize / 2, ySize / 2, zSize / 2), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 1.0)};
	//FRONT, RIGHT, DOWN
	vertices[3] = vertex{
		glm::vec3(xSize / 2, -ySize / 2, zSize / 2), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0)};
	vertices[4] = vertex{glm::vec3(xSize / 2, -ySize / 2, zSize / 2),
						 glm::vec3(0.0, -1.0, 0.0),
						 glm::vec2(1.0, 1.0)};
	vertices[5] = vertex{
		glm::vec3(xSize / 2, -ySize / 2, zSize / 2), glm::vec3(1.0, 0.0, 0.0), glm::vec2(0.0, 0.0)};
	//FRONT, LEFT, DOWN
	vertices[6] = vertex{glm::vec3(-xSize / 2, -ySize / 2, zSize / 2),
						 glm::vec3(0.0, 0.0, 1.0),
						 glm::vec2(0.0, 0.0)};
	vertices[7] = vertex{glm::vec3(-xSize / 2, -ySize / 2, zSize / 2),
						 glm::vec3(0.0, -1.0, 0.0),
						 glm::vec2(0.0, 1.0)};
	vertices[8] = vertex{glm::vec3(-xSize / 2, -ySize / 2, zSize / 2),
						 glm::vec3(-1.0, 0.0, 0.0),
						 glm::vec2(1.0, 0.0)};

	//FRONT, LEFT, UP
	vertices[9] = vertex{
		glm::vec3(-xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0)};
	vertices[10] = vertex{
		glm::vec3(-xSize / 2, ySize / 2, zSize / 2), glm::vec3(0.0, 1.0, 0.0), glm::vec2(0.0, 0.0)};
	vertices[11] = vertex{glm::vec3(-xSize / 2, ySize / 2, zSize / 2),
						  glm::vec3(-1.0, 0.0, 0.0),
						  glm::vec2(1.0, 1.0)};

	//BACK, LEFT, UP
	vertices[12] = vertex{glm::vec3(xSize / 2, ySize / 2, -zSize / 2),
						  glm::vec3(0.0, 0.0, -1.0),
						  glm::vec2(0.0, 1.0)};
	vertices[13] = vertex{
		glm::vec3(xSize / 2, ySize / 2, -zSize / 2), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 1.0)};
	vertices[14] = vertex{
		glm::vec3(xSize / 2, ySize / 2, -zSize / 2), glm::vec3(1.0, 0.0, 0.0), glm::vec2(1.0, 1.0)};

	//BACK, LEFT, DOWN
	vertices[15] = vertex{glm::vec3(xSize / 2, -ySize / 2, -zSize / 2),
						  glm::vec3(0.0, 0.0, -1.0),
						  glm::vec2(0.0, 0.0)};
	vertices[16] = vertex{glm::vec3(xSize / 2, -ySize / 2, -zSize / 2),
						  glm::vec3(0.0, -1.0, 0.0),
						  glm::vec2(1.0, 0.0)};
	vertices[17] = vertex{glm::vec3(xSize / 2, -ySize / 2, -zSize / 2),
						  glm::vec3(1.0, 0.0, 0.0),
						  glm::vec2(1.0, 0.0)};

	//BACK, RIGHT, DOWN
	vertices[18] = vertex{glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2),
						  glm::vec3(0.0, 0.0, -1.0),
						  glm::vec2(1.0, 0.0)};
	vertices[19] = vertex{glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2),
						  glm::vec3(0.0, -1.0, 0.0),
						  glm::vec2(0.0, 0.0)};
	vertices[20] = vertex{glm::vec3(-xSize / 2, -ySize / 2, -zSize / 2),
						  glm::vec3(-1.0, 0.0, 0.0),
						  glm::vec2(0.0, 0.0)};

	//BACK, RIGHT, UP
	vertices[21] = vertex{glm::vec3(-xSize / 2, ySize / 2, -zSize / 2),
						  glm::vec3(0.0, 0.0, -1.0),
						  glm::vec2(1.0, 1.0)};
	vertices[22] = vertex{glm::vec3(-xSize / 2, ySize / 2, -zSize / 2),
						  glm::vec3(0.0, 1.0, 0.0),
						  glm::vec2(0.0, 1.0)};
	vertices[23] = vertex{glm::vec3(-xSize / 2, ySize / 2, -zSize / 2),
						  glm::vec3(-1.0, 0.0, 0.0),
						  glm::vec2(0.0, 1.0)};

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
	indices[10] = 6;
	indices[11] = 3;

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

Box::~Box() {
	delete material;
	indices.clear();
	vertices.clear();
}
