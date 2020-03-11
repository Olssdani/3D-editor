#pragma once
#include <vector>
#include "glm/glm.hpp"

class object;
class DirectionalLight;
class PointLight;

class scene {
private:
	std::vector<object*> objects;
	DirectionalLight* dl;
	std::vector<PointLight*> pl;

public:
	scene();
	~scene();
	void addObject(object* o);
	void addPointLight(PointLight* l);
	void renderScene(const glm::mat4& projection,
					 const glm::mat4& view,
					 const glm::vec3& cameraPosition);
	void updateShaders();
	std::vector<object*>& getObjectList();
	void removeObject(const unsigned int index);
	std::vector<PointLight*>& getPointLights();
	DirectionalLight* getDirectionalLight();
};
