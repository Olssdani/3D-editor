#pragma once
#include "Object.h"
class plane : public Object {
public:
	plane(const glm::vec3& center,
		  const float sizeX,
		  const float sizeY,
		  const unsigned int squares);
	~plane();

private:
	void createMesh();
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 center;
	float sizeX, sizeY;
	unsigned int squares;
};
