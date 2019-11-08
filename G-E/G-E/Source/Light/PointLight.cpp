#include "PointLight.h"
#include "Object/Box.h"
PointLight::PointLight(glm::vec3 _Position, float _Constant, float _Linear , float _Quadratic){
	Position = _Position;
	Constant = _Constant;
	Linear = _Linear;
	Quadratic = _Quadratic;
	Light::Ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	Light::Diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	Light::Specular = glm::vec3(1.0f, 1.0f, 1.0f);

	box = new Box(1.0f, 1.0f, 1.0f);
	box->Scale(glm::vec3(0.2, 0.2, 0.2));
	box->Translate(Position);
	box->ChangeShader("Shaders/Light_Vert.glsl", "Shaders/Light_Frag.glsl");
}

Box* PointLight::getBox(){
	return box;
}

void PointLight::Send2GPU(Shader *shader, unsigned int nr){
	shader->setVec3("pointLights[" + std::to_string(nr) + "].position", Position);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].constant", Constant);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].linear", Linear);
	shader->setFloat("pointLights[" + std::to_string(nr) + "].quadratic", Quadratic);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].ambient", Ambient);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].diffuse", Diffuse);
	shader->setVec3("pointLights[" + std::to_string(nr) + "].specular", Specular);
	shader->setBool("pointLights[" + std::to_string(nr) + "].init", true);
}



void PointLight::setConstant(float _constant) {
	Constant = _constant;
}
void PointLight::setLinear(float _linear) {
	Linear = _linear;
}
void PointLight::setQuadratic(float _quadratic) {
	Quadratic = _quadratic;
}

float PointLight::getConstant() {
	return Constant;
}
float PointLight::getLinear() {
	return Linear;
}
float PointLight::getQuadratic() {
	return Quadratic;
}