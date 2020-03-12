#pragma once
#include "light.h"
#include "imgui.h"
#include "glm/glm.hpp"
#include <glm\gtc\type_ptr.hpp>

class directionalLight : public light {
private:
	glm::vec3 direction;

public:
	directionalLight() {
		this->direction = glm::vec3(0.0, -1.0, 0.0);
		this->ambient = diffuse = specular = glm::vec3(1.0f);
		this->ambientIntensity = 0.1f;
		this->diffuseIntensity = 0.3f;
		this->specularIntensity = 0.1f;
		this->name = "Directional Light";
	}
	directionalLight(glm::vec3 direction,
					 glm::vec3 ambient = glm::vec3(1.0),
					 glm::vec3 diffuse = glm::vec3(1.0),
					 glm::vec3 specular = glm::vec3(1.0))
		: direction(direction) {
		this->ambientIntensity = 0.1f;
		this->diffuseIntensity = 0.3f;
		this->specularIntensity = 0.1f;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->name = "Directional Light";
	}

	void send2Gpu(const shader* shader, const unsigned int nr) const override {
		shader->setVec3("dirLight[" + std::to_string(nr) + "].direction", direction);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].ambient", ambient * ambientIntensity);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].diffuse", diffuse * diffuseIntensity);
		shader->setVec3("dirLight[" + std::to_string(nr) + "].specular",
						specular * specularIntensity);
	}

	void guiRender() {
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
		int misc_flags = ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview |
						 ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoLabel;
		ImGui::ColorEdit3("MyColor##3", glm::value_ptr(lightColor), misc_flags);
		ambient = diffuse = specular = lightColor;
		Separator();
	}
};
