#include "PointLight.h"
#include "Object/box.h"
#include "glm/glm.hpp"
#include <glm\gtc\type_ptr.hpp>

PointLight::PointLight(glm::vec3 _position, float _constant, float _linear, float _quadratic) {
	position = _position;
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
	ambientIntensity = 0.01f;
	diffuseIntensity = 0.8f, specularIntensity = 1.0f;
	Light::ambient = glm::vec3(1.0f);
	Light::diffuse = glm::vec3(1.0f);
	Light::specular = glm::vec3(1.0f);

	box = new Box(1.0f, 1.0f, 1.0f);
	box->Scale(glm::vec3(0.2, 0.2, 0.2));
	box->Translate(position);
	box->ChangeShader("Shaders/Light_Vert.glsl", "Shaders/Light_Frag.glsl");
}

Box* PointLight::getBox() {
	return box;
}

void PointLight::send2Gpu(const Shader* shader, const unsigned int nr) const {
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

void PointLight::setConstant(float _constant) {
	constant = _constant;
}
void PointLight::setLinear(float _linear) {
	linear = _linear;
}
void PointLight::setQuadratic(float _quadratic) {
	quadratic = _quadratic;
}

float PointLight::getConstant() {
	return constant;
}

float PointLight::getLinear() {
	return linear;
}

float PointLight::getQuadratic() {
	return quadratic;
}

void PointLight::guiRender() {
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

void PointLight::renderVisualization(const glm::mat4& projection,
									 const glm::mat4& view,
									 const glm::vec3& cameraPosition) {
	box->setTranslation(position);
	box->getMaterial()->setColor(lightColor);
	box->RenderNoLight(projection, view, cameraPosition);
}
