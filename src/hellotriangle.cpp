#include "hellotriangle.h"
#if defined(TUTORIEL_VK_OS_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(TUTORIEL_VK_OS_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "../external/glfw/include/GLFW/glfw3native.h"
#include <array>
#include <vector>
#include <string>

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
	std::cout << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

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

	std::vector<const char*> explicitLayers;
	if (explicitLayerAvailable("VK_LAYER_KHRONOS_validation")) {
		explicitLayers.push_back("VK_LAYER_KHRONOS_validation");
	}
	instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(explicitLayers.size());
	instanceCreateInfo.ppEnabledLayerNames = explicitLayers.data();

	std::vector<const char*> instanceExtensions;
	if (instanceExtensionAvailable("VK_EXT_debug_utils")) {
		instanceExtensions.push_back("VK_EXT_debug_utils");
	}
	if (instanceExtensionAvailable("VK_KHR_surface")) {
		instanceExtensions.push_back("VK_KHR_surface");
	}
#if defined(TUTORIEL_VK_OS_WINDOWS)
	if (instanceExtensionAvailable("VK_KHR_win32_surface")) {
		instanceExtensions.push_back("VK_KHR_win32_surface");
	}
#elif defined(TUTORIEL_VK_OS_LINUX)
	if (instanceExtensionAvailable("VK_KHR_xlib_surface")) {
		instanceExtensions.push_back("VK_KHR_xlib_surface");
	}
#endif
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
	TUTORIEL_VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));

	// Creation du messager de debug
	VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
	debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	debugMessengerCreateInfo.pNext = nullptr;
	debugMessengerCreateInfo.flags = 0;
	debugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	debugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	debugMessengerCreateInfo.pfnUserCallback = debugCallback;
	debugMessengerCreateInfo.pUserData = nullptr;

	auto createDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
	TUTORIEL_VK_CHECK(createDebugUtilsMessengerEXT(m_instance, &debugMessengerCreateInfo, nullptr, &m_debugMessenger));

	// Creation de la fenetre
	if (!glfwInit()) {
		std::cout << "Une erreur a eu lieu lors de l'initialisation de GLFW." << std::endl;
	}
	m_window = glfwCreateWindow(1280, 720, "TutorielVulkanFR", nullptr, nullptr);

	// Creation de la surface
#if defined(TUTORIEL_VK_OS_WINDOWS)
	HWND handle = glfwGetWin32Window(m_window);
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = nullptr;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = reinterpret_cast<HINSTANCE>(GetWindowLongPtr(handle, GWLP_HINSTANCE));
	surfaceCreateInfo.hwnd = handle;

	auto createWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(m_instance, "vkCreateWin32SurfaceKHR");
	TUTORIEL_VK_CHECK(createWin32SurfaceKHR(m_instance, &surfaceCreateInfo, nullptr, &m_surface));
#elif defined(TUTORIEL_VK_OS_LINUX)
	m_display = XOpenDisplay(NULL);
	Window handle = glfwGetX11Window(m_window);
	VkXlibSurfaceCreateInfoKHR surfaceCreateInfo = {};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = nullptr;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.dpy = m_display;
	surfaceCreateInfo.window = handle;

	auto createXlibSurfaceKHR = (PFN_vkCreateXlibSurfaceKHR)vkGetInstanceProcAddr(m_instance, "vkCreateXlibSurfaceKHR");
	TUTORIEL_VK_CHECK(createXlibSurfaceKHR(m_instance, &surfaceCreateInfo, nullptr, &m_surface));
#endif

	// Sélection du GPU
	uint32_t physicalDeviceCount;
	vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);
	if (physicalDeviceCount == 0) {
		std::cout << "Aucun GPU supportant Vulkan n'a ete trouve." << std::endl;
		exit(1);
	}
	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, physicalDevices.data());

	m_physicalDevice = physicalDevices[0];

	// Afficher quelques informations sur le GPU choisi
	VkPhysicalDeviceProperties2 physicalDeviceProperties2 = {};
	physicalDeviceProperties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
	physicalDeviceProperties2.pNext = nullptr;
	vkGetPhysicalDeviceProperties2(m_physicalDevice, &physicalDeviceProperties2);

	std::string physicalDeviceType;
	switch (physicalDeviceProperties2.properties.deviceType) {
	case VK_PHYSICAL_DEVICE_TYPE_OTHER:
		physicalDeviceType = "Autre";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		physicalDeviceType = "Integre";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		physicalDeviceType = "Discret";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		physicalDeviceType = "Virtuel";
		break;
	case VK_PHYSICAL_DEVICE_TYPE_CPU:
		physicalDeviceType = "CPU";
		break;
	}

	std::string driverVersion = std::to_string(VK_API_VERSION_MAJOR(physicalDeviceProperties2.properties.driverVersion)) + "."
		+ std::to_string(VK_API_VERSION_MINOR(physicalDeviceProperties2.properties.driverVersion)) + "."
		+ std::to_string(VK_API_VERSION_PATCH(physicalDeviceProperties2.properties.driverVersion));
	if (physicalDeviceProperties2.properties.vendorID == 4318) { // NVIDIA
		uint32_t major = (physicalDeviceProperties2.properties.driverVersion >> 22) & 0x3ff;
		uint32_t minor = (physicalDeviceProperties2.properties.driverVersion >> 14) & 0x0ff;
		uint32_t patch = (physicalDeviceProperties2.properties.driverVersion >> 6) & 0x0ff;
		driverVersion = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
	}
#if defined(NTSH_OS_WINDOWS)
	else if (physicalDeviceProperties2.properties.vendorID == 0x8086) { // Intel
		uint32_t major = (physicalDeviceProperties2.properties.driverVersion >> 14);
		uint32_t minor = (physicalDeviceProperties2.properties.driverVersion) & 0x3fff;
		driverVersion = std::to_string(major) + "." + std::to_string(minor);
	}
#endif

	std::cout << "Nom du GPU : " << physicalDeviceProperties2.properties.deviceName << std::endl;
	std::cout << "Type du GPU : " << physicalDeviceType << std::endl;
	std::cout << "Version du driver : " << driverVersion << std::endl;
}

void HelloTriangle::update() {
	// Recuperation des evenements sur les fenetres
	glfwPollEvents();
}

void HelloTriangle::destroy() {
	// Destruction de la surface
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);

#if defined(TUTORIEL_VK_OS_LINUX)
	// Fermeture du Display Xlib
	XCloseDisplay(m_display);
#endif

	// Destruction de la fenetre
	glfwTerminate();

	// Destruction du messager de debug
	auto destroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
	destroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);

	// Destruction de l'instance
	vkDestroyInstance(m_instance, nullptr);
}

bool HelloTriangle::shouldClose() {
	return glfwWindowShouldClose(m_window);
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

	std::cout << "Layer " << layerName << "n'est pas disponible.";
	return false;
}

bool HelloTriangle::instanceExtensionAvailable(const char* extensionName) {
	uint32_t instanceExtensionPropertyCount;
	TUTORIEL_VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionPropertyCount, nullptr));
	std::vector<VkExtensionProperties> instanceExtensionProperties(instanceExtensionPropertyCount);
	TUTORIEL_VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionPropertyCount, instanceExtensionProperties.data()));

	for (const VkExtensionProperties& availableExtension : instanceExtensionProperties) {
		if (strcmp(availableExtension.extensionName, extensionName) == 0) {
			return true;
		}
	}

	std::cout << "Extension d'instance " << extensionName << "n'est pas disponible.";
	return false;
}
