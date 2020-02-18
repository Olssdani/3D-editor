#pragma once
#include "Object.h"
class Box :	public Object
{
public:
	Box(float _xSize = 1.0f, float _ySize = 1.0f, float _zSize = 1.0f);
	~Box();

private:
	float xSize, ySize, zSize;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	void CreateMesh();
};

