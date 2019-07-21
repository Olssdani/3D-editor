#pragma once
#include <vector>
#include "Object.h"
class Scene {
private:
	std::vector<Object> objects;
	DirectionalLight DL;
	std::vector<PointLight> PL;


public:
};