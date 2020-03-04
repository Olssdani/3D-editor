#pragma once
#ifndef Utilities_H
#define Utilities_H
#include "Utilities.h"
#endif
#include <vector>
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Material/Material.h"
#include "imgui.h"
#include "Mesh.h"

/*
	Base class for all different objects in the scene
*/
class Object{
protected:
	/*
		Variable Definition
	*/
	//Shader
	Shader *shader;
	Material *material;
	std::vector<Mesh> meshes;
	//Buffer objects
	unsigned int VBO, VAO, EBO;
	
	//Shaderpaths
	const char* VertPath;
	const char* FragPath;
	const char* GeoPath;
	//Number of triangels that is being draw;
	unsigned int DrawSize;
	glm::mat4 model = glm::mat4(1.0f);

	std::string name;
	int ID;

	static int object_counter;

	/*
		Protected member functions
	*/
	//Create and fill buffers
	void CreateBuffers(std::vector<vertex>& vert, std::vector<unsigned int>& ind) {
		meshes.push_back(Mesh(vert, ind));
	}

public:

	Object() {
		material = new Material(shader);
		ID = object_counter++;
	}

	/*
	public member functions
	*/
	//Render the scene
	void Render(glm::mat4 &projection, glm::mat4 &view, glm::vec3 CameraPos, DirectionalLight &Dirligth, std::vector<PointLight*> &PointLights){
		//Start shader
		shader->use();

		//Send Lights to shader
		Dirligth.send2Gpu(shader,0);
		int counter = 0;

		for each (PointLight *p in PointLights){
			p->send2Gpu(shader, counter);
			counter++;
		}

		//Send variable to shader
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);
		shader->setVec3("CameraPos", CameraPos);
		

		material->send2GPU(shader);

		for (auto m : meshes) {
			m.Draw(shader);
		}
	}

	void RenderNoLight(const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 CameraPos ){
		//Start shader
		shader->use();

		//Sendvairable to shader
		shader->setMat4("projection", projection);
		shader->setMat4("view", view);
		shader->setMat4("model", model);
		shader->setVec3("CameraPos", CameraPos);
		material->send2GPU(shader);
		//Bind the VAO and draw the vertex
		for (auto m : meshes) {
			m.Draw(shader);
		}
	}

	//Create shader with specified paths.
	void SetShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr){
		VertPath = vertexPath;
		FragPath = fragmentPath;
		GeoPath = geometryPath;
		shader = new Shader(vertexPath, fragmentPath, geometryPath);
	}
	
	//Update the shader with same shaderlink
	void UpdateShader(){
		glDeleteProgram(shader->ID);
		shader = new Shader(VertPath, FragPath, GeoPath);
		if (material->isTextureSet()) {
			shader->use();
			shader->setInt("material.diffuse", 0);
		}
	}
	//Change to another shader
	void ChangeShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr){
		VertPath = vertexPath;
		FragPath = fragmentPath;
		GeoPath = geometryPath;
		UpdateShader();
	}

	void Translate(glm::vec3 &T){
		model = glm::translate(T)*model;
	}

	void setTranslation(glm::vec3 &T) {
		model[3][0] = T.x;
		model[3][1] = T.y;
		model[3][2] = T.z;
	}

	void RotateX(float angle){
		model = glm::rotate(angle, glm::vec3(1.0, 0.0, 0.0)) *model;
	}

	void RotateY(float angle){
		model = glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0)) *model;
	}

	void RotateZ(float angle){
		model = glm::rotate(angle, glm::vec3(0.0, 0.0, 1.0)) *model;
	}

	void Scale(glm::vec3 S){
		model = glm::scale(S)*model;
	}

	void setName(const std::string _name){
		name = _name;
	}

	std::string getName(){
		return name;
	}

	int getID(){
		return ID;
	}

	Material* getMaterial(){
		return material;
	}

	Shader* getShader(){
		return shader;
	}

	void renderGui(){
		ImGui::Text("Entity name: ");
		ImGui::SameLine();
		ImGui::Text(name.c_str());
		ImGui::Separator();


		ImGui::Text("Transformation: ");
		{
			float translate[3] = { model[3][0], model[3][1], model[3][2]};
			ImGui::Text("Position: ");
			ImGui::SameLine();
			ImGui::DragFloat3("Transalte", translate, 0.01f, 0.01f, 0.01f);
			model[3][0] = translate[0];
			model[3][1] = translate[1];
			model[3][2] = translate[2];	

			float scale[3] = { model[0][0], model[1][1], model[2][2] };
			ImGui::Text("Scale: ");
			ImGui::SameLine();
			ImGui::DragFloat3("Scale", scale, 0.01f, 0.01f, 0.01f);
			model[0][0] = scale[0];
			model[1][1] = scale[1];
			model[2][2] = scale[2];

		}

		ImGui::Separator();

		ImGui::Text("Material: ");
		{
			material->renderGui();
		}
	}
};