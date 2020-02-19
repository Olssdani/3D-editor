#pragma once
#include "Light.h"
#include "imgui.h"

class DirectionalLight: public Light
{
private:
	glm::vec3 direction;

public:
	DirectionalLight(){
		direction = glm::vec3(0.0, -1.0, 0.0);
		ambient = diffuse = specular = lightColor = glm::vec3(1.0f);
		ambientIntensity = 0.1f;
		diffuseIntensity = 0.3f;
		specularIntensity = 0.1f;
		name = "Directional Light";
	}
	DirectionalLight(glm::vec3 _direction , glm::vec3 _ambient = glm::vec3(1.0), glm::vec3 _diffuse = glm::vec3(1.0), glm::vec3 _specular = glm::vec3(1.0))
		:direction(_direction) {
		ambientIntensity = 0.1f;
		diffuseIntensity = 0.3f;
		specularIntensity = 0.1f;
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
		name = "Directional Light";
	}

	void send2Gpu(const Shader *shader, const unsigned int nr ) override {	
		shader->setVec3("dirLight[" + std::to_string(nr) + "].direction", direction);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].ambient", ambient * ambientIntensity);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].diffuse", diffuse * diffuseIntensity);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].specular", specular * specularIntensity);
	}

	void renderGui() {
		using namespace ImGui;

		Text("Entity name: ");
		SameLine();
		Text(name.c_str());
		Separator();

		Text("Light Properties: ");
		
		Text("Light Direction: ");
		DragFloat3("Direction", glm::value_ptr(direction), 0.1f, -1.0f, 1.0f);
		
		Text("Ambient Intensity: ");
		DragFloat("Ambient", &ambientIntensity, 0.01f, 0, 1.0f);
		
		Text("Diffuse Intensity: ");
		DragFloat("Diffuse", &diffuseIntensity, 0.01f, 0, 1.0f);
		
		Text("Specular Intensity: ");
		DragFloat("Specular", &specularIntensity, 0.01f, 0, 1.0f);

		Text("Light Color: ");
		static bool alpha_preview = true;
		static bool alpha_half_preview = false;
		static bool drag_and_drop = true;
		static bool options_menu = true;
		int misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoLabel;
		ImGui::ColorEdit3("MyColor##3", glm::value_ptr(lightColor), misc_flags);
		ambient = diffuse = specular = lightColor;
		Separator();
	}
};











