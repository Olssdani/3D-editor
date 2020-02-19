#pragma once
#include "Light.h"
#include "imgui.h"
class DirectionalLight: public Light
{
private:
	/*
		Variable  definition
	*/
	glm::vec3 Direction;

public:
	/*
		Constructor
	*/
	/*DirectionalLight()
		:Direction(glm::vec3(0.0, -1.0, 0.0)) {

	}*/

	DirectionalLight(glm::vec3 _Direction = glm::vec3(0.0, -1.0, 0.0), glm::vec3 _Ambient = glm::vec3(1.0), glm::vec3 _Diffuse = glm::vec3(1.0), glm::vec3 _Specular = glm::vec3(1.0))
		:Direction(_Direction)
	{
		Ambient = _Ambient;
		Diffuse = _Diffuse;
		Specular = _Specular;
		name = "Directional Light";
	
	}
	/*
	Functions
	*/
	void Send2GPU(Shader *shader, unsigned int nr ) override
	{	
		shader->setVec3("dirLight[" + std::to_string(nr) + "].direction", Direction);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].ambient", Ambient);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].diffuse", Diffuse);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].specular", Specular);
	}

	void renderGui() {
		ImGui::Text("Entity name: ");
		ImGui::SameLine();
		ImGui::Text(name.c_str());
		ImGui::Separator();
	}

};











