#include "Render/render.h"
#include <iostream>
int main() {
	render r;

	if(!r.init()) {
		std::cout << "Unable to initalize render" << std::endl;
		return 0;
	}
	r.renderScene();
	return 0;
}
