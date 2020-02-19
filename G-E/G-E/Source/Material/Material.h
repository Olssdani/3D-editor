#pragma once
#include "glm/glm.hpp"
#include "shader.h"
#include "imgui.h"
#include "Misc/WindowsUtil.h"
#include "Texture/Texture.h"

class Material {

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	float Color[3];
	//texture
	bool textureEnable = false;
	Texture texture;
	Shader *shader;

public:
	Material(Shader *_shader) {
		shader = _shader;
		Color[0] = Color[1] = Color[2] = 1.0f;
		ambient = glm::vec3(1.0f);
		diffuse = glm::vec3(1.0f);
		specular = glm::vec3(1.0f);
		shininess = 32;
		textureEnable = false;
	}

	Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) 
	{
		this->ambient = _ambient;
		this->diffuse = _diffuse;
		this->specular = _specular;
		this->shininess = _shininess;
		this->textureEnable = false;
	}
	Material(glm::vec3 _color, float _shininess) 
	{
		this->ambient = _color;
		this->diffuse = _color;
		this->specular = _color;
		this->Color[0] = _color.x;
		this->Color[1] = _color.y;
		this->Color[2] = _color.z ;
		this->shininess = _shininess;
		this->textureEnable = false;
	}


	void setColor(glm::vec3 _color) 
	{
		this->ambient = _color;
		this->diffuse = _color;
		this->specular = _color;
	}
	void setColor(float _color[]) 
	{
		glm::vec3 temp;
		temp.x = _color[0];
		temp.y = _color[1];
		temp.z = _color[2];
		this->ambient = temp;
		this->diffuse = temp;
		this->specular = temp;
	}

	void setAmbient(glm::vec3 _ambient) 
	{
		this->ambient = _ambient;
	}
	void setAmbient(float _ambient []) 
	{
		this->ambient.x = _ambient[0];
		this->ambient.y = _ambient[1];
		this->ambient.z = _ambient[2];
	}

	void setDiffuse(glm::vec3 _diffuse) 
	{
		this->diffuse = _diffuse;
	}
	void setSpecular(glm::vec3 _specular) 
	{
		this->specular = _specular;
	}

	void setShininess(float _shininess) 
	{
		this->shininess = _shininess;
	}

	//Get functions
	glm::vec3 getAmbient() 
	{
		return this->ambient;
	}

	glm::vec3 getDiffuse() 
	{
		return this->diffuse;
	}
	glm::vec3 getSpecular() 
	{
		return this->specular;
	}

	float getShininess() 
	{
		return this->shininess;
	}

	bool isTextureSet()
	{
		return textureEnable;
	}

	void setTexture(const char* url)
	{
		texture = Texture(url);
		textureEnable = true;
		glDeleteProgram(shader->ID);
		shader = new Shader("Shaders/Vert.glsl", "Shaders/textureFrag.fs", "Shaders/Geo.glsl");
		shader->setInt("material.diffuse", 0);
	}

	void deleteTexture()
	{
		textureEnable = false;
		glDeleteProgram(shader->ID);
 		shader = new Shader("Shaders/Vert.glsl", "Shaders/Frag.fs", "Shaders/Geo.glsl");
	}



	void send2GPU(Shader *shader) 
	{
		if (textureEnable) {
			texture.bindTexture();
			shader->setFloat("material.shininess", this->shininess);
		}
		else {
			shader->setVec3("material.ambient", this->ambient);
			shader->setVec3("material.diffuse", this->diffuse);
			shader->setVec3("material.specular", this->specular);
			shader->setFloat("material.shininess", this->shininess);
		}

	}

	void renderGui() 
	{
		ImGui::Text("Color");
		ImGui::SameLine();
		ImGui::ColorEdit3("", Color);
		for (int i = 0; i < 3; ++i) {
			ambient[i] = Color[i];
			diffuse[i] = Color[i];
			specular[i] = Color[i];
		}
		ImGui::Text("Shininess:");
		ImGui::SameLine();
		ImGui::DragFloat("", &shininess, 0.01f, 0.00f, 100.0f);

		if (textureEnable) 
		{
			ImGui::Text("Texture is set");
			ImGui::SameLine();
			if (ImGui::Button("Delete Texture")) 
			{
				deleteTexture();
			}
		}
		else {
			if (ImGui::Button("Add Texture")) 
			{
				std::string fileName = wUtil::openFileExplorer();
				setTexture(fileName.c_str());
			}
		}


	}
};
