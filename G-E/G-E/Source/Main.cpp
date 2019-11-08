#define STB_IMAGE_IMPLEMENTATION
#include "Render/Render.h"
int Object::object_counter = 1;
int Light::counter = 0;
int main()
{
	Render render;
	render.Rendering();
	return 0;
}
