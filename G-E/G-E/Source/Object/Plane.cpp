#include "Plane.h"



Plane::Plane(const glm::vec3 &_center, const float _sizeX, const float _sizeY, const unsigned int _squares)
{
	center = _center;
	sizeX = _sizeX;
	sizeY = _sizeY;
	squares = _squares;
	createMesh();
	Object::material = new Material();
	//Connect mesh to buffers
	Object::CreateBuffers(vertices, indices);
	DrawSize = indices.size();
	//Clear unessary data
	vertices.clear();
	indices.clear();

	//Set standard shader
	shader = new Shader("Shaders/Vert.glsl", "Shaders/Frag.glsl", "Shaders/Geo.glsl");
}


Plane::~Plane()
{
}
//Creating the mesh
void Plane::createMesh()
{
	//Initialize size of vertices and indices
	//Since we need one more vertex than squares, the size of the vector is (squares+1)*(squares+1)
	//We have 2 triangle per sqaure and three indices per triangle
	vertices.resize((squares+1)*(squares+1));
	//indices.resize(2 * squares*squares * 3);
	//Square size!
	float dx = sizeX / squares;
	float dy = sizeY / squares;
	//Set vertices
	for (size_t i = 0; i < squares + 1; i++)
	{
		float y = -(sizeY / 2) + dy * i;
		
		for (size_t j = 0; j < squares + 1; j++)
		{
			float x = -(sizeX / 2) + dx * j;
			vertices[j + i * (squares + 1)] = Vertex{ glm::vec3(x,center.y, y), glm::vec3(0,1,0),glm::vec2((float)j/(float)squares,(float)i/(float)squares) };
		}
	}

	//Set indices
	int counter_squares = 0;
	int vertX = squares + 1;
	for (size_t i = 0; i < squares; i++)
	{
		for (size_t j = 0; j < squares; j++)
		{
			//triangle 1
			indices.push_back(i*vertX + j);
			indices.push_back((i + 1)*vertX + j);
			indices.push_back((i+1)* vertX + j + 1);

			//triangle 2
			indices.push_back(i*vertX + j);		
			indices.push_back((i+1)*vertX + j + 1);
			indices.push_back(i *vertX + j + 1);
		}
	}



}