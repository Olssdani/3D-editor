#include "scene.h"
#include "Object/Object.h"
#include "Object/Box.h"
#include "Object/plane.h"
#include "Object/model.h"

scene::scene() {
	plane* planeObject = new plane(glm::vec3(0, -5, 0), 50.0f, 50.0f, 10);
	planeObject->setName("Plane");
	planeObject->getMaterial()->setTexture("Resources/Textures/wall.jpg");
	planeObject->getMaterial()->setShininess(32);
	objects.push_back(planeObject);
	dl = new DirectionalLight();
}

scene::~scene() {
	delete dl;
}

void scene::addObject(Object* o) {
	objects.push_back(o);
}
void scene::addPointLight(PointLight* l) {
	pl.push_back(l);
}

void scene::renderScene(const glm::mat4& projection,
						const glm::mat4& view,
						const glm::vec3& cameraPosition) {

	for(PointLight* p : pl) {
		p->renderVisualization(projection, view, cameraPosition);
	}

	for(Object* o : objects) {
		o->Render(projection, view, cameraPosition, dl, pl);
	}
}

void scene::updateShaders() {
	for(Object* o : objects) {
		o->UpdateShader();
	}
}

std::vector<Object*>& scene::getObjectList() {
	return objects;
}

void scene::removeObject(const unsigned int index) {
	objects.erase(objects.begin() + index);
}

std::vector<PointLight*>& scene::getPointLights() {
	return pl;
}

DirectionalLight* scene::getDirectionalLight() {
	return dl;
}
