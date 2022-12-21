#include "hellotriangle.h"

int main() {
	HelloTriangle helloTriangle;
	helloTriangle.init();

	while (!helloTriangle.shouldClose()) {
		helloTriangle.update();
	}

	helloTriangle.destroy();

	return 0;
}