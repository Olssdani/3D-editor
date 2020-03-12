#pragma once
#include "GUI/gui.h"
#include <vector>
#include "mesh.h"

class material;
class pointLight;
class directionalLight;

class object : public gui {
protected:
	shader* shaderObject;
	material* materialObject;
	std::vector<mesh> meshes;
	const char *vertPath, *fragPath, *geoPath;
	unsigned int drawSize;
	glm::mat4 model = glm::mat4(1.0f);
	std::string name;
	int id;
	static int objectCounter;

	void createBuffers(std::vector<vertex>& vert, std::vector<unsigned int>& ind);

public:
	object();

	void render(const glm::mat4& projection,
				const glm::mat4& view,
				const glm::vec3& cameraPos,
				const directionalLight* dirligth,
				const std::vector<pointLight*>& pointLights);
	void
	renderNoLight(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& CameraPos);
	void
	setShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	void updateShader();
	void changeShader(const char* vertexPath,
					  const char* fragmentPath,
					  const char* geometryPath = nullptr);

	void translate(glm::vec3& T);
	void setTranslation(glm::vec3& T);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void scale(glm::vec3 S);
	void setName(const std::string& name);
	std::string getName();
	int getID();
	material* getMaterial();
	shader* getShader();
	void guiRender();
};
