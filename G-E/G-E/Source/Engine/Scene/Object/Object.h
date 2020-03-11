#pragma once
#include "GUI/gui.h"
#include <vector>
#include "Mesh.h"
#include "Material/Material.h"

class Material;
class PointLight;
class DirectionalLight;

class object : public gui {
protected:
	Shader* shader;
	Material* material;
	std::vector<Mesh> meshes;
	const char* VertPath;
	const char* FragPath;
	const char* GeoPath;
	unsigned int drawSize;
	glm::mat4 model = glm::mat4(1.0f);
	std::string name;
	int ID;
	static int object_counter;
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
	void guiRender();
};
