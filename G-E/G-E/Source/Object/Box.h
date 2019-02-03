#pragma once
#include "Object.h"
class Box :	public Object
{
public:
	Box(float _xSize, float _ySize, float _zSize);
	~Box();

private:
	float xSize, ySize, zSize;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	void CreateMesh();
};

