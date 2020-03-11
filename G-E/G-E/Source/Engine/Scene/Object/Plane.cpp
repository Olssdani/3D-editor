#include "plane.h"

plane::plane(const glm::vec3& center,
			 const float sizeX,
			 const float sizeY,
			 const unsigned int squares) {

	this->center = center;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->squares = squares;

	createMesh();

	object::CreateBuffers(vertices, indices);
	drawSize = indices.size();
	SetShader("Shaders/Vert.glsl", "Shaders/Frag.glsl", "Shaders/Geo.glsl");
	object::material = new Material(shader);

	vertices.clear();
	indices.clear();
}

plane::~plane() {}

void plane::createMesh() {

	vertices.resize((squares + 1) * (squares + 1));

	//Square size!
	float dx = sizeX / squares;
	float dy = sizeY / squares;

	//Set vertices
	for(size_t i = 0; i < squares + 1; i++) {
		float y = -(sizeY / 2) + dy * i;

		for(size_t j = 0; j < squares + 1; j++) {
			float x = -(sizeX / 2) + dx * j;
			vertices[j + i * (squares + 1)] =
				vertex{glm::vec3(x, center.y, y),
					   glm::vec3(0, 1, 0),
					   glm::vec2(static_cast<float>(j), static_cast<float>(i))};
		}
	}

	//Set indices
	int counter_squares = 0;
	int vertX = squares + 1;
	for(size_t i = 0; i < squares; i++) {
		for(size_t j = 0; j < squares; j++) {
			//triangle 1
			indices.push_back(i * vertX + j);
			indices.push_back((i + 1) * vertX + j);
			indices.push_back((i + 1) * vertX + j + 1);

			//triangle 2
			indices.push_back(i * vertX + j);
			indices.push_back((i + 1) * vertX + j + 1);
			indices.push_back(i * vertX + j + 1);
		}
	}
}

void plane::guiRender() {
	object::guiRender();
}
