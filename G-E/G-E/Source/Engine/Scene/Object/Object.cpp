#include "object.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Material/material.h"
#include "Scene/Light/pointLight.h"
#include "Scene/Light/directionalLight.h"

int object::objectCounter = 0;

void object::createBuffers(std::vector<vertex>& vert, std::vector<unsigned int>& ind) {
	meshes.push_back(mesh(vert, ind));
}

object::object() {
	materialObject = new material(shaderObject);
	id = objectCounter++;
}

void object::render(const glm::mat4& projection,
					const glm::mat4& view,
					const glm::vec3& cameraPos,
					const directionalLight* dirligth,
					const std::vector<pointLight*>& pointLights) {
	shaderObject->use();

	dirligth->send2Gpu(shaderObject, 0);

	unsigned int counter = 0;
	for(pointLight* p : pointLights) {
		p->send2Gpu(shaderObject, counter);
		counter++;
	}

	//Send variable to shader
	shaderObject->setMat4("projection", projection);
	shaderObject->setMat4("view", view);
	shaderObject->setMat4("model", model);
	shaderObject->setVec3("CameraPos", cameraPos);

	materialObject->send2GPU(shaderObject);

	for(mesh m : meshes) {
		m.Draw(shaderObject);
	}
}

void object::renderNoLight(const glm::mat4& projection,
						   const glm::mat4& view,
						   const glm::vec3& CameraPos) {
	shaderObject->use();

	shaderObject->setMat4("projection", projection);
	shaderObject->setMat4("view", view);
	shaderObject->setMat4("model", model);
	shaderObject->setVec3("CameraPos", CameraPos);
	materialObject->send2GPU(shaderObject);

	for(auto m : meshes) {
		m.Draw(shaderObject);
	}
}

void object::setShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	vertPath = vertexPath;
	fragPath = fragmentPath;
	geoPath = geometryPath;
	shaderObject = new shader(vertexPath, fragmentPath, geometryPath);
}

void object::updateShader() {
	glDeleteProgram(shaderObject->ID);
	shaderObject = new shader(vertPath, fragPath, geoPath);
	if(materialObject->isTextureSet()) {
		shaderObject->use();
		shaderObject->setInt("material.diffuse", 0);
	}
}

void object::changeShader(const char* vertexPath,
						  const char* fragmentPath,
						  const char* geometryPath) {
	vertPath = vertexPath;
	fragPath = fragmentPath;
	geoPath = geometryPath;
	updateShader();
}

void object::translate(glm::vec3& T) {
	model = glm::translate(T) * model;
}

void object::setTranslation(glm::vec3& T) {
	model[3][0] = T.x;
	model[3][1] = T.y;
	model[3][2] = T.z;
}

void object::rotateX(float angle) {
	model = glm::rotate(angle, glm::vec3(1.0, 0.0, 0.0)) * model;
}

void object::rotateY(float angle) {
	model = glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0)) * model;
}

void object::rotateZ(float angle) {
	model = glm::rotate(angle, glm::vec3(0.0, 0.0, 1.0)) * model;
}

void object::scale(glm::vec3 S) {
	model = glm::scale(S) * model;
}

void object::setName(const std::string& name) {
	this->name = name;
}

std::string object::getName() {
	return name;
}

int object::getID() {
	return id;
}

material* object::getMaterial() {
	return materialObject;
}

shader* object::getShader() {
	return shaderObject;
}

void object::guiRender() {
	ImGui::Text("Entity name: ");
	ImGui::SameLine();
	ImGui::Text(name.c_str());
	ImGui::Separator();

	ImGui::Text("Transformation: ");
	{
		float translate[3] = {model[3][0], model[3][1], model[3][2]};
		ImGui::Text("Position: ");
		ImGui::SameLine();
		ImGui::DragFloat3("Transalte", translate, 0.01f, 0.01f, 0.01f);
		model[3][0] = translate[0];
		model[3][1] = translate[1];
		model[3][2] = translate[2];

		float scale[3] = {model[0][0], model[1][1], model[2][2]};
		ImGui::Text("Scale: ");
		ImGui::SameLine();
		ImGui::DragFloat3("Scale", scale, 0.01f, 0.01f, 0.01f);
		model[0][0] = scale[0];
		model[1][1] = scale[1];
		model[2][2] = scale[2];
	}

	ImGui::Separator();

	ImGui::Text("Material: ");
	{ materialObject->renderGui(); }
}
