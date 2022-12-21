#include "hellotriangle.h"
#include <iostream>

void HelloTriangle::init() {
	std::cout << "Initialisation." << std::endl;
}

void HelloTriangle::update() {
	std::cout << "Mise a jour." << std::endl;
}

void HelloTriangle::destroy() {
	std::cout << "Destruction." << std::endl;
}

bool HelloTriangle::shouldClose() {
	return false;
}