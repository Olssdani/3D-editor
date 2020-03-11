#pragma once
#include <vector>
#include "Scene/Light/DirectionalLight.h"
#include "Scene/Light/PointLight.h"
#include "Material/Material.h"
#include "imgui.h"
#include "Mesh.h"

class object {
protected:
	/*
		Variable Definition
	*/
	//Shader
	Shader* shader;
	Material* material;
	std::vector<Mesh> meshes;
	//Buffer objects
	unsigned int VBO, VAO, EBO;

	//Shaderpaths
	const char* VertPath;
	const char* FragPath;
	const char* GeoPath;
	//Number of triangels that is being draw;
	unsigned int drawSize;
	glm::mat4 model = glm::mat4(1.0f);

	std::string name;
	int ID;

	static int object_counter;

	/*
		Protected member functions
	*/
	//Create and fill buffers
	void CreateBuffers(std::vector<vertex>& vert, std::vector<unsigned int>& ind);

public:
	object();
	void Render(const glm::mat4& projection,
				const glm::mat4& view,
				const glm::vec3 CameraPos,
				const DirectionalLight* Dirligth,
				const std::vector<PointLight*>& PointLights);
	void
	RenderNoLight(const glm::mat4& projection, const glm::mat4& view, const glm::vec3 CameraPos);
	void
	SetShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	void UpdateShader();
	void ChangeShader(const char* vertexPath,
					  const char* fragmentPath,
					  const char* geometryPath = nullptr);

	void Translate(glm::vec3& T);
	void setTranslation(glm::vec3& T);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void Scale(glm::vec3 S);
	void setName(const std::string _name);
	std::string getName();
	int getID();
	Material* getMaterial();
	Shader* getShader();
	void renderGui();
};
