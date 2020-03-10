#pragma once
#include "glm/glm.hpp"
#include "Render/shader.h"

class texture;

class Material {

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	float color[3];
	bool textureEnable = false;
	texture * textureObject;
	Shader *shader;

public:
	Material(Shader *_shader);
	Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess);
	Material(glm::vec3 _color, float _shininess);

	void setColor(glm::vec3 _color);
	void setColor(float _color[]);
	void setAmbient(glm::vec3 _ambient);
	void setAmbient(float _ambient[]);
	void setDiffuse(glm::vec3 _diffuse);
	void setSpecular(glm::vec3 _specular);		
	void setShininess(float _shininess);
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getShininess();
	bool isTextureSet();
	void setTexture(const char* url);
	void deleteTexture();
	void send2GPU(Shader *shader);
	void renderGui();
};
