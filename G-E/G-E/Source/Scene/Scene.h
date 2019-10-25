#pragma once
#include <vector>
#include "Object/Box.h"
#include "Object/Object.h"
#include "Object/Plane.h"

class Scene {
private:

	//Variables
	std::vector<Object*> objects;
	DirectionalLight DL;
	std::vector<PointLight> PL;
	Plane *plane;


public:

	Scene()
	{
		plane =new Plane(glm::vec3(0, -5, 0), 100.0f, 100.0f, 1);
		plane->setName("Plane");
		plane->getMaterial()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

		plane->getMaterial()->setShininess(32);
		objects.push_back(plane);
		DL = DirectionalLight(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f));

		PointLight p1 = PointLight(glm::vec3(0.0, 0.0, 3.0), 1.0f, 0.09f, 0.032f);
		p1.SetAmbient(glm::vec3(0.01f, 0.01f, 0.01f));
		p1.SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
		p1.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		PL.push_back(p1);
		PointLight p2 = PointLight(glm::vec3(7.0, 0.0, 0.0), 1.0f, 0.09f, 0.032f);
		p2.SetAmbient(glm::vec3(0.01f, 0.01f, 0.01f));
		p2.SetDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
		p2.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
		PL.push_back(p2);
	}
	void addObject(Object *o) {
		objects.push_back(o);
	}

	void renderScene(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPosition) {
		for each (Object* o in objects)
		{
			o->Render(projection, view, cameraPosition, DL, PL);
		}

		for each (PointLight p in PL)
		{
			p.getBox()->RenderNoLight(projection, view, cameraPosition);
		}
	}

	std::vector<Object*> getObjectList() {
		return objects;
	}

	std::vector<PointLight> getPointLights() {
		return PL;
	}

	DirectionalLight getDirectionalLight() {
		return DL;
	}
};