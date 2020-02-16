#pragma once
#include "shader.h"
#ifndef Utilities_H
#define Utilities_H
#include "Utilities.h"
#endif
#include <vector>
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Texture/Texture.h"
#include "Material/Material.h"

/*
	Base class for all different objects in the scene
*/
//Vertex struct to contain all Vertex data
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Object 
{
protected:
	/*
		Variable Definition
	*/
	//Shader
	Shader *shader;
	Material *material;
	//Buffer objects
	unsigned int VBO, VAO, EBO;
	//Shaderpaths
	const char* VertPath;
	const char* FragPath;
	const char* GeoPath;
	//Number of triangels that is being draw;
	unsigned int DrawSize;
	glm::mat4 model = glm::mat4(1.0f);
	//texture
	bool texture_enable =false;
	Texture texture;
	std::string name;
	int ID;

	static int object_counter;


	/*
		Protected member functions
	*/
	//Create and fill buffers
	void CreateBuffers(std::vector<Vertex> &vert, std::vector<unsigned int> &ind)
	{
		//MOVE THIS WHEN OBJECT CLASS HAS BEEN REDESIGNED, SHOULD BE IN CONSTRUCTOR
		ID =object_counter++;

		// Create the buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//Bind the vertex buffer object
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(Vertex), &vert[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(unsigned int), &ind[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		
		//Unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//Unbind the VAO
		glBindVertexArray(0);
	}

public:

	Object() {
		material =new Material(glm::vec3(1.0f, 1.0f, 1.0f), 32);
	}

	/*
	public member functions
	*/
	//Render the scene
	void Render(glm::mat4 &projection, glm::mat4 &view, glm::vec3 CameraPos, DirectionalLight &Dirligth, std::vector<PointLight*> &PointLights)
	{
		//Start shader
		shader->use();

		//Send Lights to shader
		Dirligth.Send2GPU(shader,0);
		int counter = 0;

		for each (PointLight *p in PointLights){
			p->Send2GPU(shader, counter);
			counter++;
		}


		//Send variable to shader
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);
		shader->setVec3("CameraPos", CameraPos);
		
		//Bind the VAO and draw the vertex
		if (texture_enable){
			texture.bindTexture();
			shader->setFloat("material.shininess", material->getShininess());
		}
		else {
			material->send2GPU(shader);
		}
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, DrawSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	void RenderNoLight(glm::mat4 &projection, glm::mat4 &view, glm::vec3 CameraPos )
	{
		//Start shader
		shader->use();

		//Sendvairable to shader
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);
		shader->setVec3("CameraPos", CameraPos);
	
		//Bind the VAO and draw the vertex
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, DrawSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	//Create shader with specified paths.
	void SetShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		VertPath = vertexPath;
		FragPath = fragmentPath;
		GeoPath = geometryPath;
		shader = new Shader(vertexPath, fragmentPath, geometryPath);
	}
	
	//Update the shader with same shaderlink
	void UpdateShader()
	{
		glDeleteProgram(shader->ID);
		shader = new Shader(VertPath, FragPath, GeoPath);
	}
	//Change to another shader
	void ChangeShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
	{
		VertPath = vertexPath;
		FragPath = fragmentPath;
		GeoPath = geometryPath;
		UpdateShader();
	}

	void Translate(glm::vec3 &T)
	{
		model = glm::translate(T)*model;
	}

	void RotateX(float angle)
	{
		model = glm::rotate(angle, glm::vec3(1.0, 0.0, 0.0)) *model;
	}
	void RotateY(float angle)
	{
		model = glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0)) *model;
	}
	void RotateZ(float angle)
	{
		model = glm::rotate(angle, glm::vec3(0.0, 0.0, 1.0)) *model;
	}
	void Scale(glm::vec3 S)
	{
		model = glm::scale(S)*model;
	}

	void setTexture(const char* url)
	{
		texture = Texture(url);
		texture_enable = true;
		ChangeShader("Shaders/Vert.glsl", "Shaders/textureFrag.fs", "Shaders/Geo.glsl");
		shader->setInt("material.diffuse", 0);
	}

	void setName(const std::string _name) {
		name = _name;
	}

	std::string getName() {
		return name;
	}

	int getID() {
		return ID;
	}

	Material* getMaterial() {
		return material;
	}
};