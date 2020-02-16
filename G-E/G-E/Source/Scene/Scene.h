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
	std::vector<PointLight*> PL;
	Plane *plane;


public:

	Scene()
	{
		plane =new Plane(glm::vec3(0, -5, 0), 50.0f, 50.0f, 10);
		plane->setName("Plane");
		plane->setTexture("D:/Programmering/G-E/G-E/G-E/Textures/wall.jpg");
		//plane->getMaterial()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		plane->getMaterial()->setShininess(32);
		objects.push_back(plane);
		DL = DirectionalLight(glm::vec3(-0.2, -1.0, -0.3), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
	}
	void addObject(Object *o) {
		objects.push_back(o);
	}
	void addPointLight(PointLight *l) {
		PL.push_back(l);
	}

	void renderScene(glm::mat4 projection, glm::mat4 view, glm::vec3 cameraPosition) {
		
		for each (PointLight* p in PL)
		{
			p->getBox()->RenderNoLight(projection, view, cameraPosition);
		}

		for each (Object* o in objects)
		{
			o->Render(projection, view, cameraPosition, DL, PL);
		}


	}

	void updateShaders() {
		for each(Object* o in objects)
		{
			o->UpdateShader();
		}
	}

	std::vector<Object*> getObjectList() {
		return objects;
	}

	std::vector<PointLight*> getPointLights() {
		return PL;
	}

	DirectionalLight* getDirectionalLight() {
		return &DL;
	}
};