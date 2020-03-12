#pragma once
#include <vector>
#include "glm/glm.hpp"

class object;
class directionalLight;
class pointLight;

class scene {
private:
	std::vector<object*> objects;
	directionalLight* dl;
	std::vector<pointLight*> pl;

public:
	scene();
	~scene();
	void addObject(object* o);
	void addPointLight(pointLight* l);
	void renderScene(const glm::mat4& projection,
					 const glm::mat4& view,
					 const glm::vec3& cameraPosition);
	void updateShaders();
	std::vector<object*>& getObjectList();
	void removeObject(const unsigned int index);
	std::vector<pointLight*>& getPointLights();
	directionalLight* getDirectionalLight();
};
