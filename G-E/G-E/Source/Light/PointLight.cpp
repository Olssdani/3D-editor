#include "PointLight.h"
#include "Object/Box.h"
PointLight::PointLight(glm::vec3 _position, float _constant, float _linear , float _quadratic){
	position = _position;
	constant = _constant;
	linear = _linear;
	quadratic = _quadratic;
	Light::ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	Light::diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	Light::specular = glm::vec3(1.0f, 1.0f, 1.0f);

	box = new Box(1.0f, 1.0f, 1.0f);
	box->Scale(glm::vec3(0.2, 0.2, 0.2));
	box->Translate(position);
	box->ChangeShader("Shaders/Light_Vert.glsl", "Shaders/Light_Frag.glsl");
}

Box* PointLight::getBox() {
	return box;
}

void PointLight::send2Gpu(const Shader *shader, const unsigned int nr) {
	shader->setVec3("pointLights[" + std::to_string(nr) + "].position", position);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].constant", constant);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].linear", linear);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].quadratic", quadratic);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].ambient", ambient);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].diffuse", diffuse);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].specular", specular);
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

void PointLight::renderGui() {
	ImGui::Text("Entity name: ");
	ImGui::SameLine();
	ImGui::Text(name.c_str());
	ImGui::Separator();

	{
		float translate[3] = { position[0], position[1], position[2] };
		ImGui::Text("Position: ");
		ImGui::SameLine();
		ImGui::DragFloat3("", translate, 0.01f, 0.01f, 0.01f);
		position[0] = translate[0];
		position[1] = translate[1];
		position[2] = translate[2];
	}
}

void PointLight::renderVisualization(const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &cameraPosition) {
	box->setTranslation(position);
	box->RenderNoLight(projection, view, cameraPosition);
}