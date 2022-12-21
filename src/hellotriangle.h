#include <iostream>

#define TUTORIEL_VK_CHECK(f) \
	do { \
		int64_t check = f; \
		if (check) { \
			std::cout << "Vulkan Error.\nError code: " << check << "\nFile: " << __FILE__ << "\nFunction: " << #f << "\nLine: " << __LINE__ << std::endl; \
			exit(1); \
		} \
	} while(0)

class HelloTriangle {
public:
	void init();
	void update();
	void destroy();

	bool shouldClose();
};