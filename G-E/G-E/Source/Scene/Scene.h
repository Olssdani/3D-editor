#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Object/Box.h"
#include "Object/Object.h"
#include "Object/Plane.h"
//#include "Object/Model.h"

class Scene {
private:

	//Variables
	std::vector<Object*> objects;
	DirectionalLight DL;
	std::vector<PointLight*> PL;
	Plane *plane;
	//Model ourModel = Model("D:/Programmering/G-E/G-E/G-E/Models/NanoSuit/nanosuit.fbx");

public:

	Scene()
	{
		plane =new Plane(glm::vec3(0, -5, 0), 50.0f, 50.0f, 10);
		plane->setName("Plane");
		plane->getMaterial()->setTexture("D:/Programmering/G-E/G-E/G-E/Textures/wall.jpg");
		//plane->getMaterial()->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		plane->getMaterial()->setShininess(32);
		objects.push_back(plane);

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
			p->renderVisualization(projection, view, cameraPosition);
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

	std::vector<Object*>& getObjectList() {
		return objects;
	}

	void removeObject(const unsigned int index) {
		objects.erase(objects.begin() + index);
	}

	std::vector<PointLight*>& getPointLights() {
		return PL;
	}

	DirectionalLight* getDirectionalLight() {
		return &DL;
	}
};

#endif // !SCENE_H
