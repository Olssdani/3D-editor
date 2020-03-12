#include "pointLight.h"
#include "Object/box.h"
#include "glm/glm.hpp"
#include <glm\gtc\type_ptr.hpp>
#include "Object/Material/material.h"

pointLight::pointLight(glm::vec3 position, float constant, float linear, float quadratic) {
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->ambientIntensity = 0.01f;
	this->diffuseIntensity = 0.8f;
	this->specularIntensity = 1.0f;
	light::ambient = glm::vec3(1.0f);
	light::diffuse = glm::vec3(1.0f);
	light::specular = glm::vec3(1.0f);

	b = new box(1.0f, 1.0f, 1.0f);
	b->scale(glm::vec3(0.2, 0.2, 0.2));
	b->translate(position);
	b->changeShader("Shaders/Light_Vert.glsl", "Shaders/Light_Frag.glsl");
}

box* pointLight::getBox() {
	return b;
}

void pointLight::send2Gpu(const shader* shader, const unsigned int nr) const {
	shader->setVec3("pointLights[" + std::to_string(nr) + "].position", position);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].constant", constant);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].linear", linear);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].quadratic", quadratic);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].ambient", ambient * ambientIntensity);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].diffuse", diffuse * diffuseIntensity);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].specular",
					specular * specularIntensity);
	shader->setBool("pointLights[" + std::to_string(nr) + "].init", true);
}

void pointLight::setConstant(float constant) {
	this->constant = constant;
}
void pointLight::setLinear(float linear) {
	this->linear = linear;
}
void pointLight::setQuadratic(float quadratic) {
	this->quadratic = quadratic;
}

float pointLight::getConstant() {
	return constant;
}

float pointLight::getLinear() {
	return linear;
}

float pointLight::getQuadratic() {
	return quadratic;
}

void pointLight::guiRender() {
	using namespace ImGui;

	Text("Entity name: ");
	SameLine();
	Text(name.c_str());
	Separator();

	{
		float translate[3] = {position[0], position[1], position[2]};
		Text("Position: ");
		SameLine();
		DragFloat3("", translate, 0.01f, 0.01f, 0.01f);
		position[0] = translate[0];
		position[1] = translate[1];
		position[2] = translate[2];
	}
	Separator();

	Text("Light Properties: ");

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

	Text("Constant: ");
	DragFloat("Constant", &constant, 0.01f, 0, 100.0f);

	Text("Linear: ");
	DragFloat("Linear", &linear, 0.001f, 0, 5.0f, "%.3f");

	Text("Quadratic: ");
	DragFloat("Quadratic", &quadratic, 0.0001f, 0, 5.0f, "%.4f");

	Separator();
}

void pointLight::renderVisualization(const glm::mat4& projection,
									 const glm::mat4& view,
									 const glm::vec3& cameraPosition) {
	b->setTranslation(position);
	b->getMaterial()->setColor(lightColor);
	b->renderNoLight(projection, view, cameraPosition);
}
