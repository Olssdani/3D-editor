#include "Render/Render.h"
#include "Scene/Object/Plane.h"
#include "Scene/Scene.h"
int Object::object_counter = 1;
int Light::counter = 0;

int main()
{
	Render render;
	render.Rendering();
	return 0;
}
