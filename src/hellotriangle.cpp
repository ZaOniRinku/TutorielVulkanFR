#include "hellotriangle.h"
#include <array>
#include <vector>

void HelloTriangle::init() {
	// Creation de l'instance
	VkApplicationInfo applicationInfo = {};
	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pNext = nullptr;
	applicationInfo.pApplicationName = "Tutoriel Vulkan FR";
	applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	applicationInfo.pEngineName = "Tutoriel Vulkan FR";
	applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
	applicationInfo.apiVersion = VK_API_VERSION_1_1;

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pNext = nullptr;
	instanceCreateInfo.flags = 0;
	instanceCreateInfo.pApplicationInfo = &applicationInfo;
	std::array<const char*, 1> explicitLayers = { "VK_LAYER_KHRONOS_validation" };
	if (explicitLayerAvailable(explicitLayers[0])) {
		instanceCreateInfo.enabledLayerCount = 1;
		instanceCreateInfo.ppEnabledLayerNames = explicitLayers.data();
	}
	else {
		std::cout << "Layer " << explicitLayers[0] << " is not available." << std::endl;
		instanceCreateInfo.enabledLayerCount = 0;
		instanceCreateInfo.ppEnabledLayerNames = nullptr;
	}
	std::vector<const char*> instanceExtensions;
	instanceExtensions.push_back("VK_EXT_debug_utils");
	instanceExtensions.push_back("VK_KHR_surface");
#if defined(TUTORIEL_VK_OS_WINDOWS)
	instanceExtensions.push_back("VK_KHR_win32_surface");
#elif defined(TUTORIEL_VK_OS_LINUX)
	instanceExtensions.push_back("VK_KHR_xlib_surface");
#endif
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	TUTORIEL_VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));
}

void HelloTriangle::update() {
}

void HelloTriangle::destroy() {
}

bool HelloTriangle::shouldClose() {
	return false;
}

bool HelloTriangle::explicitLayerAvailable(const char* layerName) {
	uint32_t instanceLayerPropertyCount;
	TUTORIEL_VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, nullptr));
	std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerPropertyCount);
	TUTORIEL_VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, instanceLayerProperties.data()));

	for (const VkLayerProperties& availableLayer : instanceLayerProperties) {
		if (strcmp(availableLayer.layerName, layerName) == 0) {
			return true;
		}
	}

	return false;
}
