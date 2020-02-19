#pragma once
#include "Light.h"
#include "imgui.h"
class DirectionalLight: public Light
{
private:
	glm::vec3 direction;

public:
	DirectionalLight(glm::vec3 _direction = glm::vec3(0.0, -1.0, 0.0), glm::vec3 _ambient = glm::vec3(1.0), glm::vec3 _diffuse = glm::vec3(1.0), glm::vec3 _specular = glm::vec3(1.0))
		:direction(_direction) {
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
		name = "Directional Light";
	}

	void send2Gpu(const Shader *shader, const unsigned int nr ) override {	
		shader->setVec3("dirLight[" + std::to_string(nr) + "].direction", direction);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].ambient", ambient);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].diffuse", diffuse);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].specular", specular);
	}

	void renderGui() {
		ImGui::Text("Entity name: ");
		ImGui::SameLine();
		ImGui::Text(name.c_str());
		ImGui::Separator();
	}
};











