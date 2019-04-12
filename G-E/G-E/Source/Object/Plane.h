#pragma once
#include "Object.h"
class Plane :
	public Object
{
public:
	Plane(const glm::vec3 &_center, const float _sizeX, const float _sizeY, const unsigned int _squares);
	~Plane();


private:
	void createMesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 center;
	float sizeX, sizeY;
	unsigned int squares;
};

