#include "renderingengine.h"

int main() {
	RenderingEngine renderingEngine;
	renderingEngine.init();

	while (!renderingEngine.shouldClose()) {
		renderingEngine.update();
	}

	renderingEngine.destroy();

	return 0;
}