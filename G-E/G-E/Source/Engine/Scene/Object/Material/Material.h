#pragma once
#include "glm/glm.hpp"

class texture;
class shader;

class material {

private:
	glm::vec3 ambient, diffuse, specular;
	float shininess;
	float color[3];
	bool textureEnable = false;
	texture* textureObject;
	shader* shaderObject;

public:
	material(shader* shader);
	material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	material(glm::vec3 color, float shininess);

	void setColor(glm::vec3 color);
	void setColor(float color[]);
	void setAmbient(glm::vec3 ambient);
	void setAmbient(float ambient[]);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setShininess(float shininess);
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getShininess();
	bool isTextureSet();
	void setTexture(const char* url);
	void deleteTexture();
	void send2GPU(shader* shader);
	void renderGui();
};
