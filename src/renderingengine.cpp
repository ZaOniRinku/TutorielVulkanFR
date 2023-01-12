#include "renderingengine.h"
#if defined(TUTORIEL_VK_OS_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(TUTORIEL_VK_OS_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "../external/glfw/include/GLFW/glfw3native.h"
#include "../external/glslang/glslang/Include/ShHandle.h"
#include "../external/glslang/SPIRV/GlslangToSpv.h"
#include "../external/glslang/StandAlone/DirStackFileIncluder.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"
#include <array>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <cstdlib>

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
	std::cout << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

void RenderingEngine::init() {
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
	VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));

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
	VK_CHECK(createDebugUtilsMessengerEXT(m_instance, &debugMessengerCreateInfo, nullptr, &m_debugMessenger));

	// Creation de la fenetre
	if (!glfwInit()) {
		std::cout << "Une erreur a eu lieu lors de l'initialisation de GLFW." << std::endl;
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
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
	VK_CHECK(createWin32SurfaceKHR(m_instance, &surfaceCreateInfo, nullptr, &m_surface));
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
	VK_CHECK(createXlibSurfaceKHR(m_instance, &surfaceCreateInfo, nullptr, &m_surface));
#endif

	// Selection du GPU
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

	// Trouver une famille de queues supportant les operations graphiques
	uint32_t queueFamilyPropertyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyPropertyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());

	m_graphicsQueueFamilyIndex = 0;
	for (const VkQueueFamilyProperties& queueFamilyProperty : queueFamilyProperties) {
		if (queueFamilyProperty.queueCount > 0 && queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			VkBool32 presentSupport;
			vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, m_graphicsQueueFamilyIndex, m_surface, &presentSupport);
			if (presentSupport) {
				break;
			}
		}
		m_graphicsQueueFamilyIndex++;
	}

	// Creation du device logique
	float queuePriority = 1.0f;
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.pNext = nullptr;
	deviceQueueCreateInfo.flags = 0;
	deviceQueueCreateInfo.queueFamilyIndex = m_graphicsQueueFamilyIndex;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceDescriptorIndexingFeatures physicalDeviceDescriptorIndexingFeatures = {};
	physicalDeviceDescriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES;
	physicalDeviceDescriptorIndexingFeatures.pNext = nullptr;
	physicalDeviceDescriptorIndexingFeatures.shaderSampledImageArrayNonUniformIndexing = VK_TRUE;
	physicalDeviceDescriptorIndexingFeatures.shaderStorageBufferArrayNonUniformIndexing = VK_TRUE;
	physicalDeviceDescriptorIndexingFeatures.descriptorBindingPartiallyBound = VK_TRUE;
	physicalDeviceDescriptorIndexingFeatures.runtimeDescriptorArray = VK_TRUE;

	VkPhysicalDeviceDynamicRenderingFeatures physicalDeviceDynamicRenderingFeatures = {};
	physicalDeviceDynamicRenderingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;
	physicalDeviceDynamicRenderingFeatures.pNext = &physicalDeviceDescriptorIndexingFeatures;
	physicalDeviceDynamicRenderingFeatures.dynamicRendering = VK_TRUE;

	VkPhysicalDeviceSynchronization2Features physicalDeviceSynchronization2Features = {};
	physicalDeviceSynchronization2Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SYNCHRONIZATION_2_FEATURES;
	physicalDeviceSynchronization2Features.pNext = &physicalDeviceDynamicRenderingFeatures;
	physicalDeviceSynchronization2Features.synchronization2 = VK_TRUE;

	VkPhysicalDeviceFeatures physicalDeviceFeatures = {};
	physicalDeviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = &physicalDeviceSynchronization2Features;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledLayerCount = 0;
	deviceCreateInfo.ppEnabledLayerNames = nullptr;

	std::vector<const char*> deviceExtensions;
	if (deviceExtensionAvailable("VK_KHR_swapchain")) {
		deviceExtensions.push_back("VK_KHR_swapchain");
	}
	if (deviceExtensionAvailable("VK_KHR_create_renderpass2")) {
		deviceExtensions.push_back("VK_KHR_create_renderpass2");
	}
	if (deviceExtensionAvailable("VK_KHR_depth_stencil_resolve")) {
		deviceExtensions.push_back("VK_KHR_depth_stencil_resolve");
	}
	if (deviceExtensionAvailable("VK_KHR_dynamic_rendering")) {
		deviceExtensions.push_back("VK_KHR_dynamic_rendering");
	}
	if (deviceExtensionAvailable("VK_KHR_synchronization2")) {
		deviceExtensions.push_back("VK_KHR_synchronization2");
	}
	if (deviceExtensionAvailable("VK_KHR_maintenance3")) {
		deviceExtensions.push_back("VK_KHR_maintenance3");
	}
	if (deviceExtensionAvailable("VK_EXT_descriptor_indexing")) {
		deviceExtensions.push_back("VK_EXT_descriptor_indexing");
	}
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

	deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;
	VK_CHECK(vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device));

	// Recuperation de la queue creee
	vkGetDeviceQueue(m_device, m_graphicsQueueFamilyIndex, 0, &m_graphicsQueue);

	// Initialisation de l'allocateur de memoire
	VmaAllocatorCreateInfo vmaAllocatorCreateInfo = {};
	vmaAllocatorCreateInfo.flags = 0;
	vmaAllocatorCreateInfo.physicalDevice = m_physicalDevice;
	vmaAllocatorCreateInfo.device = m_device;
	vmaAllocatorCreateInfo.preferredLargeHeapBlockSize = 0;
	vmaAllocatorCreateInfo.pAllocationCallbacks = nullptr;
	vmaAllocatorCreateInfo.pDeviceMemoryCallbacks = nullptr;
	vmaAllocatorCreateInfo.pHeapSizeLimit = nullptr;
	vmaAllocatorCreateInfo.pVulkanFunctions = nullptr;
	vmaAllocatorCreateInfo.instance = m_instance;
	vmaAllocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_1;
	VK_CHECK(vmaCreateAllocator(&vmaAllocatorCreateInfo, &m_allocator));

	// Creation de la swapchain
	createSwapchain(VK_NULL_HANDLE);

	// Creation du layout de descriptor set
	VkDescriptorSetLayoutBinding cameraDescriptorSetLayoutBinding = {};
	cameraDescriptorSetLayoutBinding.binding = 0;
	cameraDescriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	cameraDescriptorSetLayoutBinding.descriptorCount = 1;
	cameraDescriptorSetLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	cameraDescriptorSetLayoutBinding.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutBinding objectsDescriptorSetLayoutBinding = {};
	objectsDescriptorSetLayoutBinding.binding = 1;
	objectsDescriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	objectsDescriptorSetLayoutBinding.descriptorCount = 1;
	objectsDescriptorSetLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	objectsDescriptorSetLayoutBinding.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutBinding texturesDescriptorSetLayoutBinding = {};
	texturesDescriptorSetLayoutBinding.binding = 2;
	texturesDescriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	texturesDescriptorSetLayoutBinding.descriptorCount = 524288;
	texturesDescriptorSetLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	texturesDescriptorSetLayoutBinding.pImmutableSamplers = nullptr;

	std::array<VkDescriptorBindingFlags, 3> descriptorBindingFlags = { 0, 0, VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT };
	VkDescriptorSetLayoutBindingFlagsCreateInfo descriptorSetLayoutBindingFlagsCreateInfo = {};
	descriptorSetLayoutBindingFlagsCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
	descriptorSetLayoutBindingFlagsCreateInfo.pNext = nullptr;
	descriptorSetLayoutBindingFlagsCreateInfo.bindingCount = static_cast<uint32_t>(descriptorBindingFlags.size());
	descriptorSetLayoutBindingFlagsCreateInfo.pBindingFlags = descriptorBindingFlags.data();

	std::array<VkDescriptorSetLayoutBinding, 3> descriptorSetLayoutBindings = { cameraDescriptorSetLayoutBinding, objectsDescriptorSetLayoutBinding, texturesDescriptorSetLayoutBinding };
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
	descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutCreateInfo.pNext = &descriptorSetLayoutBindingFlagsCreateInfo;
	descriptorSetLayoutCreateInfo.flags = 0;
	descriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32_t>(descriptorSetLayoutBindings.size());
	descriptorSetLayoutCreateInfo.pBindings = descriptorSetLayoutBindings.data();
	VK_CHECK(vkCreateDescriptorSetLayout(m_device, &descriptorSetLayoutCreateInfo, nullptr, &m_descriptorSetLayout));

	// Creation du pipeline graphique
	createGraphicsPipeline();

	// Creation des command pools et allocation des command buffers
	m_renderingCommandPools.resize(m_framesInFlight);
	m_renderingCommandBuffers.resize(m_framesInFlight);

	VkCommandPoolCreateInfo commandPoolCreateInfo = {};
	commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	commandPoolCreateInfo.pNext = nullptr;
	commandPoolCreateInfo.flags = 0;
	commandPoolCreateInfo.queueFamilyIndex = m_graphicsQueueFamilyIndex;

	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.pNext = nullptr;
	commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocateInfo.commandBufferCount = 1;

	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		VK_CHECK(vkCreateCommandPool(m_device, &commandPoolCreateInfo, nullptr, &m_renderingCommandPools[i]));

		commandBufferAllocateInfo.commandPool = m_renderingCommandPools[i];
		VK_CHECK(vkAllocateCommandBuffers(m_device, &commandBufferAllocateInfo, &m_renderingCommandBuffers[i]));
	}

	// Creation des objets de synchronisation
	m_fences.resize(m_framesInFlight);
	m_acquireCompletedSemaphores.resize(m_framesInFlight);
	m_renderCompletedSemaphores.resize(m_swapchainImageCount);

	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.pNext = nullptr;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	VkSemaphoreCreateInfo semaphoreCreateInfo = {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.pNext = nullptr;
	semaphoreCreateInfo.flags = 0;

	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		VK_CHECK(vkCreateFence(m_device, &fenceCreateInfo, nullptr, &m_fences[i]));
		VK_CHECK(vkCreateSemaphore(m_device, &semaphoreCreateInfo, nullptr, &m_acquireCompletedSemaphores[i]));
	}
	for (uint32_t i = 0; i < m_swapchainImageCount; i++) {
		VK_CHECK(vkCreateSemaphore(m_device, &semaphoreCreateInfo, nullptr, &m_renderCompletedSemaphores[i]));
	}

	// Chargement de fonctions utilisees lors de l'enregistrement des commandes
	m_vkCmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)vkGetDeviceProcAddr(m_device, "vkCmdPipelineBarrier2KHR");
	m_vkCmdBeginRenderingKHR = (PFN_vkCmdBeginRenderingKHR)vkGetDeviceProcAddr(m_device, "vkCmdBeginRenderingKHR");
	m_vkCmdEndRenderingKHR = (PFN_vkCmdEndRenderingKHR)vkGetDeviceProcAddr(m_device, "vkCmdEndRenderingKHR");

	// Creation des vertex et index buffers
	VkBufferCreateInfo vertexAndIndexBufferCreateInfo = {};
	vertexAndIndexBufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	vertexAndIndexBufferCreateInfo.pNext = nullptr;
	vertexAndIndexBufferCreateInfo.flags = 0;
	vertexAndIndexBufferCreateInfo.size = 67108864;
	vertexAndIndexBufferCreateInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	vertexAndIndexBufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	vertexAndIndexBufferCreateInfo.queueFamilyIndexCount = 1;
	vertexAndIndexBufferCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;

	VmaAllocationCreateInfo vertexAndIndexBufferAllocationCreateInfo = {};
	vertexAndIndexBufferAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

	VK_CHECK(vmaCreateBuffer(m_allocator, &vertexAndIndexBufferCreateInfo, &vertexAndIndexBufferAllocationCreateInfo, &m_vertexBuffer, &m_vertexBufferAllocation, nullptr));

	vertexAndIndexBufferCreateInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	VK_CHECK(vmaCreateBuffer(m_allocator, &vertexAndIndexBufferCreateInfo, &vertexAndIndexBufferAllocationCreateInfo, &m_indexBuffer, &m_indexBufferAllocation, nullptr));

	// Creation des buffers de camera
	m_cameraBuffers.resize(m_framesInFlight);
	m_cameraBufferAllocations.resize(m_framesInFlight);

	VkBufferCreateInfo cameraBufferCreateInfo = {};
	cameraBufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	cameraBufferCreateInfo.pNext = nullptr;
	cameraBufferCreateInfo.flags = 0;
	cameraBufferCreateInfo.size = sizeof(nml::mat4) * 2;
	cameraBufferCreateInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	cameraBufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	cameraBufferCreateInfo.queueFamilyIndexCount = 1;
	cameraBufferCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;

	VmaAllocationCreateInfo cameraBufferAllocationCreateInfo = {};
	cameraBufferAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
	cameraBufferAllocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;

	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		VK_CHECK(vmaCreateBuffer(m_allocator, &cameraBufferCreateInfo, &cameraBufferAllocationCreateInfo, &m_cameraBuffers[i], &m_cameraBufferAllocations[i], nullptr));
	}

	// Creation des buffers d'objets
	m_objectsBuffers.resize(m_framesInFlight);
	m_objectsBufferAllocations.resize(m_framesInFlight);

	VkBufferCreateInfo objectsBufferCreateInfo = {};
	objectsBufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	objectsBufferCreateInfo.pNext = nullptr;
	objectsBufferCreateInfo.flags = 0;
	objectsBufferCreateInfo.size = (sizeof(nml::mat4) + sizeof(nml::vec4)) * 2048;
	objectsBufferCreateInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
	objectsBufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	objectsBufferCreateInfo.queueFamilyIndexCount = 1;
	objectsBufferCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;

	VmaAllocationCreateInfo objectsBufferAllocationCreateInfo = {};
	objectsBufferAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
	objectsBufferAllocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;

	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		VK_CHECK(vmaCreateBuffer(m_allocator, &objectsBufferCreateInfo, &objectsBufferAllocationCreateInfo, &m_objectsBuffers[i], &m_objectsBufferAllocations[i], nullptr));
	}

	// Creation du descriptor pool
	VkDescriptorPoolSize cameraDescriptorPoolSize = {};
	cameraDescriptorPoolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	cameraDescriptorPoolSize.descriptorCount = 1;

	VkDescriptorPoolSize objectsDescriptorPoolSize = {};
	objectsDescriptorPoolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	objectsDescriptorPoolSize.descriptorCount = 1;

	VkDescriptorPoolSize texturesDescriptorPoolSize = {};
	texturesDescriptorPoolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	texturesDescriptorPoolSize.descriptorCount = 524288;

	std::array<VkDescriptorPoolSize, 3> descriptorPoolSizes = { cameraDescriptorPoolSize, objectsDescriptorPoolSize, texturesDescriptorPoolSize };
	VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
	descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	descriptorPoolCreateInfo.pNext = nullptr;
	descriptorPoolCreateInfo.flags = 0;
	descriptorPoolCreateInfo.maxSets = m_framesInFlight;
	descriptorPoolCreateInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
	descriptorPoolCreateInfo.pPoolSizes = descriptorPoolSizes.data();
	VK_CHECK(vkCreateDescriptorPool(m_device, &descriptorPoolCreateInfo, nullptr, &m_descriptorPool));

	// Allocation des descriptor sets
	m_descriptorSets.resize(m_framesInFlight);
	VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
	descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	descriptorSetAllocateInfo.pNext = nullptr;
	descriptorSetAllocateInfo.descriptorPool = m_descriptorPool;
	descriptorSetAllocateInfo.descriptorSetCount = 1;
	descriptorSetAllocateInfo.pSetLayouts = &m_descriptorSetLayout;

	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		VK_CHECK(vkAllocateDescriptorSets(m_device, &descriptorSetAllocateInfo, &m_descriptorSets[i]));
	}

	// Mise a jour des descriptor sets
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		std::vector<VkWriteDescriptorSet> writeDescriptorSets;
		VkDescriptorBufferInfo cameraDescriptorBufferInfo;
		VkDescriptorBufferInfo objectsDescriptorBufferInfo;

		cameraDescriptorBufferInfo.buffer = m_cameraBuffers[i];
		cameraDescriptorBufferInfo.offset = 0;
		cameraDescriptorBufferInfo.range = sizeof(nml::mat4) * 2;

		VkWriteDescriptorSet cameraDescriptorWriteDescriptorSet = {};
		cameraDescriptorWriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		cameraDescriptorWriteDescriptorSet.pNext = nullptr;
		cameraDescriptorWriteDescriptorSet.dstSet = m_descriptorSets[i];
		cameraDescriptorWriteDescriptorSet.dstBinding = 0;
		cameraDescriptorWriteDescriptorSet.dstArrayElement = 0;
		cameraDescriptorWriteDescriptorSet.descriptorCount = 1;
		cameraDescriptorWriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		cameraDescriptorWriteDescriptorSet.pImageInfo = nullptr;
		cameraDescriptorWriteDescriptorSet.pBufferInfo = &cameraDescriptorBufferInfo;
		cameraDescriptorWriteDescriptorSet.pTexelBufferView = nullptr;
		writeDescriptorSets.push_back(cameraDescriptorWriteDescriptorSet);

		objectsDescriptorBufferInfo.buffer = m_objectsBuffers[i];
		objectsDescriptorBufferInfo.offset = 0;
		objectsDescriptorBufferInfo.range = (sizeof(nml::mat4) + sizeof(nml::vec4)) * 2048;

		VkWriteDescriptorSet objectsDescriptorWriteDescriptorSet = {};
		objectsDescriptorWriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		objectsDescriptorWriteDescriptorSet.pNext = nullptr;
		objectsDescriptorWriteDescriptorSet.dstSet = m_descriptorSets[i];
		objectsDescriptorWriteDescriptorSet.dstBinding = 1;
		objectsDescriptorWriteDescriptorSet.dstArrayElement = 0;
		objectsDescriptorWriteDescriptorSet.descriptorCount = 1;
		objectsDescriptorWriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		objectsDescriptorWriteDescriptorSet.pImageInfo = nullptr;
		objectsDescriptorWriteDescriptorSet.pBufferInfo = &objectsDescriptorBufferInfo;
		objectsDescriptorWriteDescriptorSet.pTexelBufferView = nullptr;
		writeDescriptorSets.push_back(objectsDescriptorWriteDescriptorSet);

		vkUpdateDescriptorSets(m_device, static_cast<uint32_t>(writeDescriptorSets.size()), writeDescriptorSets.data(), 0, nullptr);
	}

	m_descriptorSetsNeedUpdate.resize(m_framesInFlight);
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		m_descriptorSetsNeedUpdate[i] = false;
	}

	// Creation de l'image de profondeur
	createDepthImage();

	// Creation de l'echantillonneur de textures
	VkSamplerCreateInfo textureSamplerCreateInfo = {};
	textureSamplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	textureSamplerCreateInfo.pNext = nullptr;
	textureSamplerCreateInfo.flags = 0;
	textureSamplerCreateInfo.magFilter = VK_FILTER_LINEAR;
	textureSamplerCreateInfo.minFilter = VK_FILTER_LINEAR;
	textureSamplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	textureSamplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	textureSamplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	textureSamplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	textureSamplerCreateInfo.mipLodBias = 0.0f;
	textureSamplerCreateInfo.anisotropyEnable = VK_TRUE;
	textureSamplerCreateInfo.maxAnisotropy = 16.0f;
	textureSamplerCreateInfo.compareEnable = VK_FALSE;
	textureSamplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
	textureSamplerCreateInfo.minLod = 0.0f;
	textureSamplerCreateInfo.maxLod = VK_LOD_CLAMP_NONE;
	textureSamplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	textureSamplerCreateInfo.unnormalizedCoordinates = VK_FALSE;
	VK_CHECK(vkCreateSampler(m_device, &textureSamplerCreateInfo, nullptr, &m_textureSampler));

	// Chargement d'une texture par defaut
	loadTexture("../models/no_texture.jpg");

	// Creation de la scene
	createScene();
}

void RenderingEngine::update() {
	// Recuperation des evenements sur les fenetres
	glfwPollEvents();

	VK_CHECK(vkWaitForFences(m_device, 1, &m_fences[m_currentFrameInFlight], VK_TRUE, std::numeric_limits<uint64_t>::max()));

	// Recuperation d'un indice d'une image libre de la swapchain
	uint32_t imageIndex;
	VkResult acquireNextImageResult = vkAcquireNextImageKHR(m_device, m_swapchain, std::numeric_limits<uint64_t>::max(), m_acquireCompletedSemaphores[m_currentFrameInFlight], VK_NULL_HANDLE, &imageIndex);
	if (acquireNextImageResult == VK_ERROR_OUT_OF_DATE_KHR) {
		onResize();
	}
	else if (acquireNextImageResult != VK_SUCCESS && acquireNextImageResult != VK_SUBOPTIMAL_KHR) {
		std::cout << "Une erreur a eu lieu lors de l'acquisition de l'indice de la prochaine image de la swapchain." << std::endl;
		exit(1);
	}

	// Mise a jour du buffer de camera
	const float toRad = 3.1415926535897932384626433832795f / 180.0f;
	nml::mat4 cameraView = nml::lookAtRH(nml::vec3(0.0f, 2.0f, -3.0f), nml::vec3(0.0f), nml::vec3(0.0f, 1.0f, 0.0));
	nml::mat4 cameraProjection = nml::perspectiveRH(90.0f * toRad, m_viewport.width / m_viewport.height, 0.05f, 100.0f);
	cameraProjection[1][1] *= -1.0f;
	std::array<nml::mat4, 2> cameraMatrices{ cameraView, cameraProjection };

	void* data;
	VK_CHECK(vmaMapMemory(m_allocator, m_cameraBufferAllocations[m_currentFrameInFlight], &data));
	memcpy(data, cameraMatrices.data(), sizeof(nml::mat4) * 2);
	vmaUnmapMemory(m_allocator, m_cameraBufferAllocations[m_currentFrameInFlight]);

	// Mise a jour du buffer des objets
	VK_CHECK(vmaMapMemory(m_allocator, m_objectsBufferAllocations[m_currentFrameInFlight], &data));
	for (size_t i = 0; i < m_objects.size(); i++) {
		nml::mat4 objectModel = nml::translate(m_objects[i].position) * nml::rotate(m_objects[i].rotation.x, nml::vec3(1.0f, 0.0f, 0.0f)) * nml::rotate(m_objects[i].rotation.y, nml::vec3(0.0f, 1.0f, 0.0f)) * nml::rotate(m_objects[i].rotation.z, nml::vec3(0.0f, 0.0f, 1.0f)) * nml::scale(m_objects[i].scale);

		size_t offset = (i * (sizeof(nml::mat4) + sizeof(nml::vec4)));

		memcpy(reinterpret_cast<char*>(data) + offset, objectModel.data(), sizeof(nml::mat4));
		memcpy(reinterpret_cast<char*>(data) + offset + sizeof(nml::mat4), &m_objects[i].textureIndex, sizeof(uint32_t));
	}
	vmaUnmapMemory(m_allocator, m_objectsBufferAllocations[m_currentFrameInFlight]);

	// Mise a jour du descriptor set si necessaire
	if (m_descriptorSetsNeedUpdate[m_currentFrameInFlight]) {
		updateDescriptorSet(m_currentFrameInFlight);

		m_descriptorSetsNeedUpdate[m_currentFrameInFlight] = false;
	}

	// Reinitialisation du command buffer alloue avec le command pool
	VK_CHECK(vkResetCommandPool(m_device, m_renderingCommandPools[m_currentFrameInFlight], 0));

	// Debut de l'enregistrement du command buffer
	VkCommandBufferBeginInfo commandBufferBeginInfo = {};
	commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	commandBufferBeginInfo.pNext = nullptr;
	commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	VK_CHECK(vkBeginCommandBuffer(m_renderingCommandBuffers[m_currentFrameInFlight], &commandBufferBeginInfo));

	// Transition de layout VK_IMAGE_LAYOUT_UNDEFINED -> VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	VkImageMemoryBarrier2 undefinedToColorAttachmentOptimalImageMemoryBarrier = {};
	undefinedToColorAttachmentOptimalImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.pNext = nullptr;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.srcStageMask = VK_PIPELINE_STAGE_2_NONE;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.srcAccessMask = 0;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.srcQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.dstQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.image = m_swapchainImages[imageIndex];
	undefinedToColorAttachmentOptimalImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.subresourceRange.levelCount = 1;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
	undefinedToColorAttachmentOptimalImageMemoryBarrier.subresourceRange.layerCount = 1;

	VkDependencyInfo undefinedToColorAttachmentOptimalDependencyInfo = {};
	undefinedToColorAttachmentOptimalDependencyInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	undefinedToColorAttachmentOptimalDependencyInfo.pNext = nullptr;
	undefinedToColorAttachmentOptimalDependencyInfo.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	undefinedToColorAttachmentOptimalDependencyInfo.memoryBarrierCount = 0;
	undefinedToColorAttachmentOptimalDependencyInfo.pMemoryBarriers = nullptr;
	undefinedToColorAttachmentOptimalDependencyInfo.bufferMemoryBarrierCount = 0;
	undefinedToColorAttachmentOptimalDependencyInfo.pBufferMemoryBarriers = nullptr;
	undefinedToColorAttachmentOptimalDependencyInfo.imageMemoryBarrierCount = 1;
	undefinedToColorAttachmentOptimalDependencyInfo.pImageMemoryBarriers = &undefinedToColorAttachmentOptimalImageMemoryBarrier;

	m_vkCmdPipelineBarrier2KHR(m_renderingCommandBuffers[m_currentFrameInFlight], &undefinedToColorAttachmentOptimalDependencyInfo);

	// Lien du vertex et de l'index buffer
	VkDeviceSize vertexBufferOffset = 0;
	vkCmdBindVertexBuffers(m_renderingCommandBuffers[m_currentFrameInFlight], 0, 1, &m_vertexBuffer, &vertexBufferOffset);
	vkCmdBindIndexBuffer(m_renderingCommandBuffers[m_currentFrameInFlight], m_indexBuffer, 0, VK_INDEX_TYPE_UINT32);

	// Lien du descriptor set 0
	vkCmdBindDescriptorSets(m_renderingCommandBuffers[m_currentFrameInFlight], VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipelineLayout, 0, 1, &m_descriptorSets[m_currentFrameInFlight], 0, nullptr);

	// Debut de la passe de rendu
	VkRenderingAttachmentInfo renderingAttachmentInfo = {};
	renderingAttachmentInfo.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
	renderingAttachmentInfo.pNext = nullptr;
	renderingAttachmentInfo.imageView = m_swapchainImageViews[imageIndex];
	renderingAttachmentInfo.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	renderingAttachmentInfo.resolveMode = VK_RESOLVE_MODE_NONE;
	renderingAttachmentInfo.resolveImageView = VK_NULL_HANDLE;
	renderingAttachmentInfo.resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	renderingAttachmentInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	renderingAttachmentInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	renderingAttachmentInfo.clearValue.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	renderingAttachmentInfo.clearValue.depthStencil = { 0.0f, 0 };

	VkRenderingAttachmentInfo depthRenderingAttachmentInfo = {};
	depthRenderingAttachmentInfo.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
	depthRenderingAttachmentInfo.pNext = nullptr;
	depthRenderingAttachmentInfo.imageView = m_depthImageView;
	depthRenderingAttachmentInfo.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	depthRenderingAttachmentInfo.resolveMode = VK_RESOLVE_MODE_NONE;
	depthRenderingAttachmentInfo.resolveImageView = VK_NULL_HANDLE;
	depthRenderingAttachmentInfo.resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthRenderingAttachmentInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthRenderingAttachmentInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	depthRenderingAttachmentInfo.clearValue.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	depthRenderingAttachmentInfo.clearValue.depthStencil = { 1.0f, 0 };

	VkRenderingInfo renderingInfo = {};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
	renderingInfo.pNext = nullptr;
	renderingInfo.flags = 0;
	renderingInfo.renderArea = m_scissor;
	renderingInfo.layerCount = 1;
	renderingInfo.viewMask = 0;
	renderingInfo.colorAttachmentCount = 1;
	renderingInfo.pColorAttachments = &renderingAttachmentInfo;
	renderingInfo.pDepthAttachment = &depthRenderingAttachmentInfo;
	renderingInfo.pStencilAttachment = nullptr;
	m_vkCmdBeginRenderingKHR(m_renderingCommandBuffers[m_currentFrameInFlight], &renderingInfo);

	// Lien du pipeline graphique
	vkCmdBindPipeline(m_renderingCommandBuffers[m_currentFrameInFlight], VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);
	vkCmdSetViewport(m_renderingCommandBuffers[m_currentFrameInFlight], 0, 1, &m_viewport);
	vkCmdSetScissor(m_renderingCommandBuffers[m_currentFrameInFlight], 0, 1, &m_scissor);

	for (size_t i = 0; i < m_objects.size(); i++) {
		// Passage de l'indice de l'objet avec une push constant
		vkCmdPushConstants(m_renderingCommandBuffers[m_currentFrameInFlight], m_graphicsPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(uint32_t), &m_objects[i].index);

		// Dessin
		vkCmdDrawIndexed(m_renderingCommandBuffers[m_currentFrameInFlight], m_meshes[m_objects[i].meshIndex].indexCount, 1, m_meshes[m_objects[i].meshIndex].firstIndex, m_meshes[m_objects[i].meshIndex].vertexOffset, 0);
	}

	// Fin de la passe de rendu
	m_vkCmdEndRenderingKHR(m_renderingCommandBuffers[m_currentFrameInFlight]);

	// Transition de layout VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL -> VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	VkImageMemoryBarrier2 colorAttachmentOptimalToPresentSrcImageMemoryBarrier = {};
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.pNext = nullptr;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.dstStageMask = VK_PIPELINE_STAGE_2_NONE;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.dstAccessMask = 0;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.srcQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.dstQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.image = m_swapchainImages[imageIndex];
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.subresourceRange.levelCount = 1;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
	colorAttachmentOptimalToPresentSrcImageMemoryBarrier.subresourceRange.layerCount = 1;

	VkDependencyInfo colorAttachmentOptimalToPresentSrcDependencyInfo = {};
	colorAttachmentOptimalToPresentSrcDependencyInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	colorAttachmentOptimalToPresentSrcDependencyInfo.pNext = nullptr;
	colorAttachmentOptimalToPresentSrcDependencyInfo.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	colorAttachmentOptimalToPresentSrcDependencyInfo.memoryBarrierCount = 0;
	colorAttachmentOptimalToPresentSrcDependencyInfo.pMemoryBarriers = nullptr;
	colorAttachmentOptimalToPresentSrcDependencyInfo.bufferMemoryBarrierCount = 0;
	colorAttachmentOptimalToPresentSrcDependencyInfo.pBufferMemoryBarriers = nullptr;
	colorAttachmentOptimalToPresentSrcDependencyInfo.imageMemoryBarrierCount = 1;
	colorAttachmentOptimalToPresentSrcDependencyInfo.pImageMemoryBarriers = &colorAttachmentOptimalToPresentSrcImageMemoryBarrier;

	m_vkCmdPipelineBarrier2KHR(m_renderingCommandBuffers[m_currentFrameInFlight], &colorAttachmentOptimalToPresentSrcDependencyInfo);

	// Fin de l'enregistrement du command buffer
	VK_CHECK(vkEndCommandBuffer(m_renderingCommandBuffers[m_currentFrameInFlight]));

	// De-signalement de la fence
	VK_CHECK(vkResetFences(m_device, 1, &m_fences[m_currentFrameInFlight]));

	// Soumission des commandes a la queue du GPU
	VkPipelineStageFlags waitDstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &m_acquireCompletedSemaphores[m_currentFrameInFlight];
	submitInfo.pWaitDstStageMask = &waitDstStageMask;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_renderingCommandBuffers[m_currentFrameInFlight];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &m_renderCompletedSemaphores[imageIndex];
	VK_CHECK(vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_fences[m_currentFrameInFlight]));

	// Presentation de l'image de la swapchain a l'ecran
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = nullptr;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &m_renderCompletedSemaphores[imageIndex];
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &m_swapchain;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;
	VkResult queuePresentResult = vkQueuePresentKHR(m_graphicsQueue, &presentInfo);
	if (queuePresentResult == VK_ERROR_OUT_OF_DATE_KHR) {
		onResize();
	}
	else if (queuePresentResult != VK_SUCCESS) {
		std::cout << "Une erreur a eu lieu lors de la presentation de l'image de la swapchain." << std::endl;
		exit(1);
	}

	// Frame-in-flight suivante
	m_currentFrameInFlight = (m_currentFrameInFlight + 1) % m_framesInFlight;
}

void RenderingEngine::destroy() {
	// Attente que la queue du GPU ne soit plus utilisee
	VK_CHECK(vkQueueWaitIdle(m_graphicsQueue));

	// Destruction du descriptor pool
	vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);

	// Destruction des images de textures et de leurs vues
	for (size_t i = 0; i < m_textureImages.size(); i++) {
		vkDestroyImageView(m_device, m_textureImageViews[i], nullptr);
		vmaDestroyImage(m_allocator, m_textureImages[i], m_textureImageAllocations[i]);
	}

	// Destruction de l'echantillonneur des textures
	vkDestroySampler(m_device, m_textureSampler, nullptr);

	// Destruction des buffers d'objets
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		vmaDestroyBuffer(m_allocator, m_objectsBuffers[i], m_objectsBufferAllocations[i]);
	}

	// Destruction des buffers de camera
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		vmaDestroyBuffer(m_allocator, m_cameraBuffers[i], m_cameraBufferAllocations[i]);
	}

	// Destruction des vertex et index buffers
	vmaDestroyBuffer(m_allocator, m_indexBuffer, m_indexBufferAllocation);
	vmaDestroyBuffer(m_allocator, m_vertexBuffer, m_vertexBufferAllocation);

	// Destruction des objets de synchronisation
	for (uint32_t i = 0; i < m_swapchainImageCount; i++) {
		vkDestroySemaphore(m_device, m_renderCompletedSemaphores[i], nullptr);
	}
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		vkDestroySemaphore(m_device, m_acquireCompletedSemaphores[i], nullptr);

		vkDestroyFence(m_device, m_fences[i], nullptr);
	}

	// Destruction des command pools
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		vkDestroyCommandPool(m_device, m_renderingCommandPools[i], nullptr);
	}

	// Destruction du pipeline graphique
	vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);

	// Destruction du layout du pipeline graphique
	vkDestroyPipelineLayout(m_device, m_graphicsPipelineLayout, nullptr);

	// Destruction du layout de descriptor set
	vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);

	// Destruction de l'image de profondeur et sa vue
	vkDestroyImageView(m_device, m_depthImageView, nullptr);
	vmaDestroyImage(m_allocator, m_depthImage, m_depthImageAllocation);

	// Destruction des vues des images de la swapchain
	for (uint32_t i = 0; i < m_swapchainImageCount; i++) {
		vkDestroyImageView(m_device, m_swapchainImageViews[i], nullptr);
	}

	// Destruction de la swapchain
	vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);

	// Destruction de l'allocateur de memoire
	vmaDestroyAllocator(m_allocator);

	// Destruction du device logique
	vkDestroyDevice(m_device, nullptr);

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

bool RenderingEngine::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

bool RenderingEngine::explicitLayerAvailable(const char* layerName) {
	uint32_t instanceLayerPropertyCount;
	VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, nullptr));
	std::vector<VkLayerProperties> instanceLayerProperties(instanceLayerPropertyCount);
	VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, instanceLayerProperties.data()));

	for (const VkLayerProperties& availableLayer : instanceLayerProperties) {
		if (strcmp(availableLayer.layerName, layerName) == 0) {
			return true;
		}
	}

	std::cout << "Layer " << layerName << " n'est pas disponible.";
	return false;
}

bool RenderingEngine::instanceExtensionAvailable(const char* extensionName) {
	uint32_t instanceExtensionPropertyCount;
	VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionPropertyCount, nullptr));
	std::vector<VkExtensionProperties> instanceExtensionProperties(instanceExtensionPropertyCount);
	VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionPropertyCount, instanceExtensionProperties.data()));

	for (const VkExtensionProperties& availableExtension : instanceExtensionProperties) {
		if (strcmp(availableExtension.extensionName, extensionName) == 0) {
			return true;
		}
	}

	std::cout << "Extension d'instance " << extensionName << " n'est pas disponible.";
	return false;
}

bool RenderingEngine::deviceExtensionAvailable(const char* extensionName) {
	uint32_t deviceExtensionPropertyCount;
	VK_CHECK(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &deviceExtensionPropertyCount, nullptr));
	std::vector<VkExtensionProperties> deviceExtensionProperties(deviceExtensionPropertyCount);
	VK_CHECK(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &deviceExtensionPropertyCount, deviceExtensionProperties.data()));

	for (const VkExtensionProperties& availableExtension : deviceExtensionProperties) {
		if (strcmp(availableExtension.extensionName, extensionName) == 0) {
			return true;
		}
	}

	std::cout << "Extension de device " << extensionName << " n'est pas disponible.";
	return false;
}

void RenderingEngine::createGraphicsPipeline() {
	// Compilation des shaders
	std::string vertexShader = readAsciiFile("../shaders/model.vert");
	std::vector<uint32_t> vertexShaderSpv = compileShaderFile(vertexShader, ShaderType::Vertex);

	std::string fragmentShader = readAsciiFile("../shaders/model.frag");
	std::vector<uint32_t> fragmentShaderSpv = compileShaderFile(fragmentShader, ShaderType::Fragment);

	// Creation des modules de shaders
	VkShaderModule vertexShaderModule;
	VkShaderModuleCreateInfo vertexShaderModuleCreateInfo = {};
	vertexShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	vertexShaderModuleCreateInfo.pNext = nullptr;
	vertexShaderModuleCreateInfo.flags = 0;
	vertexShaderModuleCreateInfo.codeSize = vertexShaderSpv.size() * sizeof(uint32_t);
	vertexShaderModuleCreateInfo.pCode = vertexShaderSpv.data();
	VK_CHECK(vkCreateShaderModule(m_device, &vertexShaderModuleCreateInfo, nullptr, &vertexShaderModule));

	VkPipelineShaderStageCreateInfo vertexShaderStageCreateInfo = {};
	vertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertexShaderStageCreateInfo.pNext = nullptr;
	vertexShaderStageCreateInfo.flags = 0;
	vertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertexShaderStageCreateInfo.module = vertexShaderModule;
	vertexShaderStageCreateInfo.pName = "main";
	vertexShaderStageCreateInfo.pSpecializationInfo = nullptr;

	VkShaderModule fragmentShaderModule;
	VkShaderModuleCreateInfo fragmentShaderModuleCreateInfo = {};
	fragmentShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	fragmentShaderModuleCreateInfo.pNext = nullptr;
	fragmentShaderModuleCreateInfo.flags = 0;
	fragmentShaderModuleCreateInfo.codeSize = fragmentShaderSpv.size() * sizeof(uint32_t);
	fragmentShaderModuleCreateInfo.pCode = fragmentShaderSpv.data();
	VK_CHECK(vkCreateShaderModule(m_device, &fragmentShaderModuleCreateInfo, nullptr, &fragmentShaderModule));

	VkPipelineShaderStageCreateInfo fragmentShaderStageCreateInfo = {};
	fragmentShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragmentShaderStageCreateInfo.pNext = nullptr;
	fragmentShaderStageCreateInfo.flags = 0;
	fragmentShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragmentShaderStageCreateInfo.module = fragmentShaderModule;
	fragmentShaderStageCreateInfo.pName = "main";
	fragmentShaderStageCreateInfo.pSpecializationInfo = nullptr;

	std::array<VkPipelineShaderStageCreateInfo, 2> shaderStageCreateInfos = { vertexShaderStageCreateInfo, fragmentShaderStageCreateInfo };

	// Vertices en entree
	VkVertexInputBindingDescription vertexInputBindingDescription = {};
	vertexInputBindingDescription.binding = 0;
	vertexInputBindingDescription.stride = sizeof(Vertex);
	vertexInputBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	VkVertexInputAttributeDescription vertexPositionInputAttributeDescription = {};
	vertexPositionInputAttributeDescription.location = 0;
	vertexPositionInputAttributeDescription.binding = 0;
	vertexPositionInputAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	vertexPositionInputAttributeDescription.offset = 0;

	VkVertexInputAttributeDescription vertexNormalInputAttributeDescription = {};
	vertexNormalInputAttributeDescription.location = 1;
	vertexNormalInputAttributeDescription.binding = 0;
	vertexNormalInputAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	vertexNormalInputAttributeDescription.offset = offsetof(Vertex, normal);

	VkVertexInputAttributeDescription vertexUVInputAttributeDescription = {};
	vertexUVInputAttributeDescription.location = 2;
	vertexUVInputAttributeDescription.binding = 0;
	vertexUVInputAttributeDescription.format = VK_FORMAT_R32G32_SFLOAT;
	vertexUVInputAttributeDescription.offset = offsetof(Vertex, uv);

	std::array<VkVertexInputAttributeDescription, 3> vertexInputAttributeDescriptions = { vertexPositionInputAttributeDescription, vertexNormalInputAttributeDescription, vertexUVInputAttributeDescription };

	VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
	vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputStateCreateInfo.pNext = nullptr;
	vertexInputStateCreateInfo.flags = 0;
	vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
	vertexInputStateCreateInfo.pVertexBindingDescriptions = &vertexInputBindingDescription;
	vertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributeDescriptions.size());
	vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data();

	// Assemblement des vertices en primitives
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
	inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyStateCreateInfo.pNext = nullptr;
	inputAssemblyStateCreateInfo.flags = 0;
	inputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

	// Viewport et scissor du pipeline graphique
	VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
	viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateCreateInfo.pNext = nullptr;
	viewportStateCreateInfo.flags = 0;
	viewportStateCreateInfo.viewportCount = 1;
	viewportStateCreateInfo.pViewports = nullptr;
	viewportStateCreateInfo.scissorCount = 1;
	viewportStateCreateInfo.pScissors = nullptr;

	// Etats dynamiques
	std::array<VkDynamicState, 2> dynamicStates = { VK_DYNAMIC_STATE_SCISSOR, VK_DYNAMIC_STATE_VIEWPORT };
	VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
	dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicStateCreateInfo.pNext = nullptr;
	dynamicStateCreateInfo.flags = 0;
	dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

	// Rasterisation
	VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
	rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizationStateCreateInfo.pNext = nullptr;
	rasterizationStateCreateInfo.flags = 0;
	rasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
	rasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
	rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f;
	rasterizationStateCreateInfo.depthBiasClamp = 0.0f;
	rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f;
	rasterizationStateCreateInfo.lineWidth = 1.0f;

	// Multisampling
	VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
	multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleStateCreateInfo.pNext = nullptr;
	multisampleStateCreateInfo.flags = 0;
	multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
	multisampleStateCreateInfo.minSampleShading = 0.0f;
	multisampleStateCreateInfo.pSampleMask = nullptr;
	multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
	multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

	// Profondeur et stencil
	VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {};
	depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencilStateCreateInfo.pNext = nullptr;
	depthStencilStateCreateInfo.flags = 0;
	depthStencilStateCreateInfo.depthTestEnable = VK_TRUE;
	depthStencilStateCreateInfo.depthWriteEnable = VK_TRUE;
	depthStencilStateCreateInfo.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencilStateCreateInfo.depthBoundsTestEnable = VK_FALSE;
	depthStencilStateCreateInfo.stencilTestEnable = VK_FALSE;
	depthStencilStateCreateInfo.front = {};
	depthStencilStateCreateInfo.back = {};
	depthStencilStateCreateInfo.minDepthBounds = 0.0f;
	depthStencilStateCreateInfo.maxDepthBounds = 1.0f;

	// Melange de couleurs
	VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
	colorBlendAttachmentState.blendEnable = VK_FALSE;
	colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachmentState.colorWriteMask = { VK_COLOR_COMPONENT_R_BIT |
		VK_COLOR_COMPONENT_G_BIT |
		VK_COLOR_COMPONENT_B_BIT |
		VK_COLOR_COMPONENT_A_BIT };

	VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
	colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendStateCreateInfo.pNext = nullptr;
	colorBlendStateCreateInfo.flags = 0;
	colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
	colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
	colorBlendStateCreateInfo.attachmentCount = 1;
	colorBlendStateCreateInfo.pAttachments = &colorBlendAttachmentState;

	// Rendu dynamique
	VkPipelineRenderingCreateInfo pipelineRenderingCreateInfo = {};
	pipelineRenderingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO;
	pipelineRenderingCreateInfo.pNext = nullptr;
	pipelineRenderingCreateInfo.viewMask = 0;
	pipelineRenderingCreateInfo.colorAttachmentCount = 1;
	pipelineRenderingCreateInfo.pColorAttachmentFormats = &m_swapchainFormat;
	pipelineRenderingCreateInfo.depthAttachmentFormat = VK_FORMAT_D32_SFLOAT;
	pipelineRenderingCreateInfo.stencilAttachmentFormat = VK_FORMAT_UNDEFINED;

	// Creation du layout du pipeline graphique
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	pushConstantRange.offset = 0;
	pushConstantRange.size = sizeof(uint32_t);

	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
	pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutCreateInfo.pNext = nullptr;
	pipelineLayoutCreateInfo.flags = 0;
	pipelineLayoutCreateInfo.setLayoutCount = 1;
	pipelineLayoutCreateInfo.pSetLayouts = &m_descriptorSetLayout;
	pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
	pipelineLayoutCreateInfo.pPushConstantRanges = &pushConstantRange;
	VK_CHECK(vkCreatePipelineLayout(m_device, &pipelineLayoutCreateInfo, nullptr, &m_graphicsPipelineLayout));

	// Creation du pipeline graphique
	VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
	graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	graphicsPipelineCreateInfo.pNext = &pipelineRenderingCreateInfo;
	graphicsPipelineCreateInfo.flags = 0;
	graphicsPipelineCreateInfo.stageCount = 2;
	graphicsPipelineCreateInfo.pStages = shaderStageCreateInfos.data();
	graphicsPipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
	graphicsPipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
	graphicsPipelineCreateInfo.pTessellationState = nullptr;
	graphicsPipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
	graphicsPipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
	graphicsPipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
	graphicsPipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
	graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
	graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
	graphicsPipelineCreateInfo.layout = m_graphicsPipelineLayout;
	graphicsPipelineCreateInfo.renderPass = VK_NULL_HANDLE;
	graphicsPipelineCreateInfo.subpass = 0;
	graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
	graphicsPipelineCreateInfo.basePipelineIndex = 0;
	VK_CHECK(vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &m_graphicsPipeline));

	// Destruction des modules de shaders
	vkDestroyShaderModule(m_device, fragmentShaderModule, nullptr);
	vkDestroyShaderModule(m_device, vertexShaderModule, nullptr);
}

std::string RenderingEngine::readBinaryFile(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Le fichier binaire \"" << filePath << "\" n'a pas pu etre ouvert." << std::endl;
		exit(1);
	}
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return fileContent;
}

std::string RenderingEngine::readAsciiFile(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::in);
	if (!file.is_open()) {
		std::cout << "Le fichier ASCII \"" << filePath << "\" n'a pas pu etre ouvert." << std::endl;
		exit(1);
	}
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return fileContent;
}

std::vector<uint32_t> RenderingEngine::compileShaderFile(const std::string& shaderCode, ShaderType shaderType) {
	if (!m_glslangInitialized) {
		glslang::InitializeProcess();
		m_glslangInitialized = true;
	}

	std::vector<uint32_t> spvCode;

	const char* shaderCodeCharPtr = shaderCode.c_str();

	EShLanguage eshType;
	switch (shaderType) {
	case ShaderType::Vertex:
		eshType = EShLangVertex;
		break;

	case ShaderType::TessellationControl:
		eshType = EShLangTessControl;
		break;

	case ShaderType::TessellationEvaluation:
		eshType = EShLangTessEvaluation;
		break;

	case ShaderType::Geometry:
		eshType = EShLangGeometry;
		break;

	case ShaderType::Fragment:
		eshType = EShLangFragment;
		break;
	}

	glslang::TShader shader(eshType);
	shader.setStrings(&shaderCodeCharPtr, 1);
	int clientInputSemanticsVersion = 110;
	glslang::EshTargetClientVersion vulkanClientVersion = glslang::EShTargetVulkan_1_1;
	glslang::EShTargetLanguageVersion spvLanguageVersion = glslang::EShTargetSpv_1_2;
	shader.setEnvInput(glslang::EShSourceGlsl, eshType, glslang::EShClientVulkan, clientInputSemanticsVersion);
	shader.setEnvClient(glslang::EShClientVulkan, vulkanClientVersion);
	shader.setEnvTarget(glslang::EshTargetSpv, spvLanguageVersion);
	EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
	int defaultVersion = 460;

	// Preprocess
	const TBuiltInResource defaultTBuiltInResource = {
		/* .MaxLights = */ 32,
		/* .MaxClipPlanes = */ 6,
		/* .MaxTextureUnits = */ 32,
		/* .MaxTextureCoords = */ 32,
		/* .MaxVertexAttribs = */ 64,
		/* .MaxVertexUniformComponents = */ 4096,
		/* .MaxVaryingFloats = */ 64,
		/* .MaxVertexTextureImageUnits = */ 32,
		/* .MaxCombinedTextureImageUnits = */ 80,
		/* .MaxTextureImageUnits = */ 32,
		/* .MaxFragmentUniformComponents = */ 4096,
		/* .MaxDrawBuffers = */ 32,
		/* .MaxVertexUniformVectors = */ 128,
		/* .MaxVaryingVectors = */ 8,
		/* .MaxFragmentUniformVectors = */ 16,
		/* .MaxVertexOutputVectors = */ 16,
		/* .MaxFragmentInputVectors = */ 15,
		/* .MinProgramTexelOffset = */ -8,
		/* .MaxProgramTexelOffset = */ 7,
		/* .MaxClipDistances = */ 8,
		/* .MaxComputeWorkGroupCountX = */ 65535,
		/* .MaxComputeWorkGroupCountY = */ 65535,
		/* .MaxComputeWorkGroupCountZ = */ 65535,
		/* .MaxComputeWorkGroupSizeX = */ 1024,
		/* .MaxComputeWorkGroupSizeY = */ 1024,
		/* .MaxComputeWorkGroupSizeZ = */ 64,
		/* .MaxComputeUniformComponents = */ 1024,
		/* .MaxComputeTextureImageUnits = */ 16,
		/* .MaxComputeImageUniforms = */ 8,
		/* .MaxComputeAtomicCounters = */ 8,
		/* .MaxComputeAtomicCounterBuffers = */ 1,
		/* .MaxVaryingComponents = */ 60,
		/* .MaxVertexOutputComponents = */ 64,
		/* .MaxGeometryInputComponents = */ 64,
		/* .MaxGeometryOutputComponents = */ 128,
		/* .MaxFragmentInputComponents = */ 128,
		/* .MaxImageUnits = */ 8,
		/* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
		/* .MaxCombinedShaderOutputResources = */ 8,
		/* .MaxImageSamples = */ 0,
		/* .MaxVertexImageUniforms = */ 0,
		/* .MaxTessControlImageUniforms = */ 0,
		/* .MaxTessEvaluationImageUniforms = */ 0,
		/* .MaxGeometryImageUniforms = */ 0,
		/* .MaxFragmentImageUniforms = */ 8,
		/* .MaxCombinedImageUniforms = */ 8,
		/* .MaxGeometryTextureImageUnits = */ 16,
		/* .MaxGeometryOutputVertices = */ 256,
		/* .MaxGeometryTotalOutputComponents = */ 1024,
		/* .MaxGeometryUniformComponents = */ 1024,
		/* .MaxGeometryVaryingComponents = */ 64,
		/* .MaxTessControlInputComponents = */ 128,
		/* .MaxTessControlOutputComponents = */ 128,
		/* .MaxTessControlTextureImageUnits = */ 16,
		/* .MaxTessControlUniformComponents = */ 1024,
		/* .MaxTessControlTotalOutputComponents = */ 4096,
		/* .MaxTessEvaluationInputComponents = */ 128,
		/* .MaxTessEvaluationOutputComponents = */ 128,
		/* .MaxTessEvaluationTextureImageUnits = */ 16,
		/* .MaxTessEvaluationUniformComponents = */ 1024,
		/* .MaxTessPatchComponents = */ 120,
		/* .MaxPatchVertices = */ 32,
		/* .MaxTessGenLevel = */ 64,
		/* .MaxViewports = */ 16,
		/* .MaxVertexAtomicCounters = */ 0,
		/* .MaxTessControlAtomicCounters = */ 0,
		/* .MaxTessEvaluationAtomicCounters = */ 0,
		/* .MaxGeometryAtomicCounters = */ 0,
		/* .MaxFragmentAtomicCounters = */ 8,
		/* .MaxCombinedAtomicCounters = */ 8,
		/* .MaxAtomicCounterBindings = */ 1,
		/* .MaxVertexAtomicCounterBuffers = */ 0,
		/* .MaxTessControlAtomicCounterBuffers = */ 0,
		/* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
		/* .MaxGeometryAtomicCounterBuffers = */ 0,
		/* .MaxFragmentAtomicCounterBuffers = */ 1,
		/* .MaxCombinedAtomicCounterBuffers = */ 1,
		/* .MaxAtomicCounterBufferSize = */ 16384,
		/* .MaxTransformFeedbackBuffers = */ 4,
		/* .MaxTransformFeedbackInterleavedComponents = */ 64,
		/* .MaxCullDistances = */ 8,
		/* .MaxCombinedClipAndCullDistances = */ 8,
		/* .MaxSamples = */ 4,
		/* .maxMeshOutputVerticesNV = */ 256,
		/* .maxMeshOutputPrimitivesNV = */ 512,
		/* .maxMeshWorkGroupSizeX_NV = */ 32,
		/* .maxMeshWorkGroupSizeY_NV = */ 1,
		/* .maxMeshWorkGroupSizeZ_NV = */ 1,
		/* .maxTaskWorkGroupSizeX_NV = */ 32,
		/* .maxTaskWorkGroupSizeY_NV = */ 1,
		/* .maxTaskWorkGroupSizeZ_NV = */ 1,
		/* .maxMeshViewCountNV = */ 4,
		/* .maxMeshOutputVerticesEXT = */ 256,
		/* .maxMeshOutputPrimitivesEXT = */ 256,
		/* .maxMeshWorkGroupSizeX_EXT = */ 128,
		/* .maxMeshWorkGroupSizeY_EXT = */ 128,
		/* .maxMeshWorkGroupSizeZ_EXT = */ 128,
		/* .maxTaskWorkGroupSizeX_EXT = */ 128,
		/* .maxTaskWorkGroupSizeY_EXT = */ 128,
		/* .maxTaskWorkGroupSizeZ_EXT = */ 128,
		/* .maxMeshViewCountEXT = */ 4,
		/* .maxDualSourceDrawBuffersEXT = */ 1,

		/* .limits = */ {
			/* .nonInductiveForLoops = */ 1,
			/* .whileLoops = */ 1,
			/* .doWhileLoops = */ 1,
			/* .generalUniformIndexing = */ 1,
			/* .generalAttributeMatrixVectorIndexing = */ 1,
			/* .generalVaryingIndexing = */ 1,
			/* .generalSamplerIndexing = */ 1,
			/* .generalVariableIndexing = */ 1,
			/* .generalConstantMatrixVectorIndexing = */ 1,
		} };
	DirStackFileIncluder includer;
	includer.pushExternalLocalDirectory("../shaders/");
	std::string preprocess;
	if (!shader.preprocess(&defaultTBuiltInResource, defaultVersion, ENoProfile, false, false, messages, &preprocess, includer)) {
		std::cout << "Le preprocessing du shader a echoue.\n" << std::string(shader.getInfoLog()) << std::endl;
		exit(1);
	}

	// Parse
	const char* preprocessCharPtr = preprocess.c_str();
	shader.setStrings(&preprocessCharPtr, 1);
	if (!shader.parse(&defaultTBuiltInResource, defaultVersion, false, messages)) {
		std::cout << "Le parsing du shader a echoue.\n" << std::string(shader.getInfoLog()) << std::endl;
		exit(1);
	}

	// Link
	glslang::TProgram program;
	program.addShader(&shader);
	if (!program.link(messages)) {
		std::cout << "Le linking du shader a echoue.\n" << std::string(shader.getInfoLog()) << std::endl;
		exit(1);
	}

	// Compile
	spv::SpvBuildLogger buildLogger;
	glslang::SpvOptions spvOptions;
	glslang::GlslangToSpv(*program.getIntermediate(eshType), spvCode, &buildLogger, &spvOptions);

	return spvCode;
}

void RenderingEngine::createSwapchain(VkSwapchainKHR oldSwapchain) {
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	// Viewport et scissor
	m_viewport.x = 0.0f;
	m_viewport.y = 0.0f;
	m_viewport.width = static_cast<float>(windowWidth);
	m_viewport.height = static_cast<float>(windowHeight);
	m_viewport.minDepth = 0.0f;
	m_viewport.maxDepth = 1.0f;

	m_scissor.offset.x = 0;
	m_scissor.offset.y = 0;
	m_scissor.extent.width = static_cast<uint32_t>(windowWidth);
	m_scissor.extent.height = static_cast<uint32_t>(windowHeight);

	// Creation de la swapchain
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, m_surface, &surfaceCapabilities);
	uint32_t minImageCount = surfaceCapabilities.minImageCount + 1;
	if (surfaceCapabilities.maxImageCount > 0 && minImageCount > surfaceCapabilities.maxImageCount) {
		minImageCount = surfaceCapabilities.maxImageCount;
	}

	uint32_t surfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &surfaceFormatCount, nullptr);
	std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface, &surfaceFormatCount, surfaceFormats.data());
	m_swapchainFormat = surfaceFormats[0].format;
	VkColorSpaceKHR swapchainColorSpace = surfaceFormats[0].colorSpace;
	for (const VkSurfaceFormatKHR& surfaceFormat : surfaceFormats) {
		if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR) {
			m_swapchainFormat = surfaceFormat.format;
			swapchainColorSpace = surfaceFormat.colorSpace;
			break;
		}
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &presentModeCount, nullptr);
	std::vector<VkPresentModeKHR> presentModes(presentModeCount);
	vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface, &presentModeCount, presentModes.data());
	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;
	for (const VkPresentModeKHR& presentMode : presentModes) {
		if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			swapchainPresentMode = presentMode;
			break;
		}
		else if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			swapchainPresentMode = presentMode;
		}
	}

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.pNext = nullptr;
	swapchainCreateInfo.flags = 0;
	swapchainCreateInfo.surface = m_surface;
	swapchainCreateInfo.minImageCount = minImageCount;
	swapchainCreateInfo.imageFormat = m_swapchainFormat;
	swapchainCreateInfo.imageColorSpace = swapchainColorSpace;
	swapchainCreateInfo.imageExtent = surfaceCapabilities.currentExtent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.queueFamilyIndexCount = 0;
	swapchainCreateInfo.pQueueFamilyIndices = nullptr;
	swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = swapchainPresentMode;
	swapchainCreateInfo.clipped = VK_TRUE;
	swapchainCreateInfo.oldSwapchain = oldSwapchain;
	VK_CHECK(vkCreateSwapchainKHR(m_device, &swapchainCreateInfo, nullptr, &m_swapchain));

	VK_CHECK(vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_swapchainImageCount, nullptr));
	m_swapchainImages.resize(m_swapchainImageCount);
	VK_CHECK(vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_swapchainImageCount, m_swapchainImages.data()));

	// Le nombre de frames-in-flight ne doit pas etre superieur au nombre d'images dans la swapchain
	if (m_framesInFlight > m_swapchainImageCount) {
		m_framesInFlight = m_swapchainImageCount;
	}

	m_swapchainImageViews.resize(m_swapchainImageCount);
	for (uint32_t i = 0; i < m_swapchainImageCount; i++) {
		VkImageViewCreateInfo swapchainImageViewCreateInfo = {};
		swapchainImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		swapchainImageViewCreateInfo.pNext = nullptr;
		swapchainImageViewCreateInfo.flags = 0;
		swapchainImageViewCreateInfo.image = m_swapchainImages[i];
		swapchainImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		swapchainImageViewCreateInfo.format = m_swapchainFormat;
		swapchainImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
		swapchainImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
		swapchainImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
		swapchainImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
		swapchainImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		swapchainImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		swapchainImageViewCreateInfo.subresourceRange.levelCount = 1;
		swapchainImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		swapchainImageViewCreateInfo.subresourceRange.layerCount = 1;
		VK_CHECK(vkCreateImageView(m_device, &swapchainImageViewCreateInfo, nullptr, &m_swapchainImageViews[i]));
	}
}

void RenderingEngine::onResize() {
	// Attente que la swapchain soit libre
	VK_CHECK(vkQueueWaitIdle(m_graphicsQueue));

	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	while (windowWidth == 0 || windowHeight == 0) {
		glfwPollEvents();
		glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
	}

	// Destruction des vues des images de l'ancienne swapchain
	for (uint32_t i = 0; i < m_swapchainImageCount; i++) {
		vkDestroyImageView(m_device, m_swapchainImageViews[i], nullptr);
	}

	// Recreation de la swapchain
	createSwapchain(m_swapchain);

	// Destruction de l'image de profondeur et de sa vue
	vkDestroyImageView(m_device, m_depthImageView, nullptr);
	vmaDestroyImage(m_allocator, m_depthImage, m_depthImageAllocation);

	// Recreation de l'image de profondeur
	createDepthImage();
}

void RenderingEngine::createDepthImage() {
	int width;
	int height;
	glfwGetWindowSize(m_window, &width, &height);

	VkImageCreateInfo depthImageCreateInfo = {};
	depthImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	depthImageCreateInfo.pNext = nullptr;
	depthImageCreateInfo.flags = 0;
	depthImageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	depthImageCreateInfo.format = VK_FORMAT_D32_SFLOAT;
	depthImageCreateInfo.extent.width = static_cast<uint32_t>(width);
	depthImageCreateInfo.extent.height = static_cast<uint32_t>(height);
	depthImageCreateInfo.extent.depth = 1;
	depthImageCreateInfo.mipLevels = 1;
	depthImageCreateInfo.arrayLayers = 1;
	depthImageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	depthImageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	depthImageCreateInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	depthImageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	depthImageCreateInfo.queueFamilyIndexCount = 1;
	depthImageCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;
	depthImageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VmaAllocationCreateInfo depthImageAllocationCreateInfo = {};
	depthImageAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

	VK_CHECK(vmaCreateImage(m_allocator, &depthImageCreateInfo, &depthImageAllocationCreateInfo, &m_depthImage, &m_depthImageAllocation, nullptr));

	VkImageViewCreateInfo depthImageViewCreateInfo = {};
	depthImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	depthImageViewCreateInfo.pNext = nullptr;
	depthImageViewCreateInfo.flags = 0;
	depthImageViewCreateInfo.image = m_depthImage;
	depthImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	depthImageViewCreateInfo.format = VK_FORMAT_D32_SFLOAT;
	depthImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
	depthImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
	depthImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
	depthImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
	depthImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	depthImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
	depthImageViewCreateInfo.subresourceRange.levelCount = 1;
	depthImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	depthImageViewCreateInfo.subresourceRange.layerCount = 1;
	VK_CHECK(vkCreateImageView(m_device, &depthImageViewCreateInfo, nullptr, &m_depthImageView));

	// Transition de layout VK_IMAGE_LAYOUT_UNDEFINED -> VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
	VkCommandPool depthImageTransitionCommandPool;

	VkCommandPoolCreateInfo depthImageTransitionCommandPoolCreateInfo = {};
	depthImageTransitionCommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	depthImageTransitionCommandPoolCreateInfo.pNext = nullptr;
	depthImageTransitionCommandPoolCreateInfo.flags = 0;
	depthImageTransitionCommandPoolCreateInfo.queueFamilyIndex = m_graphicsQueueFamilyIndex;
	VK_CHECK(vkCreateCommandPool(m_device, &depthImageTransitionCommandPoolCreateInfo, nullptr, &depthImageTransitionCommandPool));

	VkCommandBuffer depthImageTransitionCommandBuffer;

	VkCommandBufferAllocateInfo depthImageTransitionCommandBufferAllocateInfo = {};
	depthImageTransitionCommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	depthImageTransitionCommandBufferAllocateInfo.pNext = nullptr;
	depthImageTransitionCommandBufferAllocateInfo.commandPool = depthImageTransitionCommandPool;
	depthImageTransitionCommandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	depthImageTransitionCommandBufferAllocateInfo.commandBufferCount = 1;
	VK_CHECK(vkAllocateCommandBuffers(m_device, &depthImageTransitionCommandBufferAllocateInfo, &depthImageTransitionCommandBuffer));

	VkCommandBufferBeginInfo depthImageTransitionBeginInfo = {};
	depthImageTransitionBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	depthImageTransitionBeginInfo.pNext = nullptr;
	depthImageTransitionBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	depthImageTransitionBeginInfo.pInheritanceInfo = nullptr;
	VK_CHECK(vkBeginCommandBuffer(depthImageTransitionCommandBuffer, &depthImageTransitionBeginInfo));

	VkImageMemoryBarrier2 undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier = {};
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.pNext = nullptr;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.srcStageMask = VK_PIPELINE_STAGE_2_NONE;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.srcAccessMask = 0;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.srcQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.dstQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.image = m_depthImage;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.subresourceRange.levelCount = 1;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
	undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier.subresourceRange.layerCount = 1;

	VkDependencyInfo undefinedToDepthStencilAttachmentOptimalDependencyInfo = {};
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.pNext = nullptr;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.memoryBarrierCount = 0;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.pMemoryBarriers = nullptr;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.bufferMemoryBarrierCount = 0;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.pBufferMemoryBarriers = nullptr;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.imageMemoryBarrierCount = 1;
	undefinedToDepthStencilAttachmentOptimalDependencyInfo.pImageMemoryBarriers = &undefinedToDepthStencilAttachmentOptimalImageMemoryBarrier;
	m_vkCmdPipelineBarrier2KHR(depthImageTransitionCommandBuffer, &undefinedToDepthStencilAttachmentOptimalDependencyInfo);

	VK_CHECK(vkEndCommandBuffer(depthImageTransitionCommandBuffer));

	VkFence depthImageTransitionFence;

	VkFenceCreateInfo depthImageTransitionFenceCreateInfo = {};
	depthImageTransitionFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	depthImageTransitionFenceCreateInfo.pNext = nullptr;
	depthImageTransitionFenceCreateInfo.flags = 0;
	VK_CHECK(vkCreateFence(m_device, &depthImageTransitionFenceCreateInfo, nullptr, &depthImageTransitionFence));

	VkSubmitInfo depthImageTransitionSubmitInfo = {};
	depthImageTransitionSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	depthImageTransitionSubmitInfo.pNext = nullptr;
	depthImageTransitionSubmitInfo.waitSemaphoreCount = 0;
	depthImageTransitionSubmitInfo.pWaitSemaphores = nullptr;
	depthImageTransitionSubmitInfo.pWaitDstStageMask = nullptr;
	depthImageTransitionSubmitInfo.commandBufferCount = 1;
	depthImageTransitionSubmitInfo.pCommandBuffers = &depthImageTransitionCommandBuffer;
	depthImageTransitionSubmitInfo.signalSemaphoreCount = 0;
	depthImageTransitionSubmitInfo.pSignalSemaphores = nullptr;
	VK_CHECK(vkQueueSubmit(m_graphicsQueue, 1, &depthImageTransitionSubmitInfo, depthImageTransitionFence));
	VK_CHECK(vkWaitForFences(m_device, 1, &depthImageTransitionFence, VK_TRUE, std::numeric_limits<uint64_t>::max()));

	vkDestroyFence(m_device, depthImageTransitionFence, nullptr);
	vkDestroyCommandPool(m_device, depthImageTransitionCommandPool, nullptr);
}

void RenderingEngine::updateDescriptorSet(uint32_t frameInFlight) {
	// Mise a jour du descriptor set
	std::vector<VkDescriptorImageInfo> texturesDescriptorImageInfos(m_textureImages.size());
	for (size_t j = 0; j < m_textureImages.size(); j++) {
		texturesDescriptorImageInfos[j].sampler = m_textureSampler;
		texturesDescriptorImageInfos[j].imageView = m_textureImageViews[j];
		texturesDescriptorImageInfos[j].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	}

	VkWriteDescriptorSet texturesDescriptorWriteDescriptorSet = {};
	texturesDescriptorWriteDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	texturesDescriptorWriteDescriptorSet.pNext = nullptr;
	texturesDescriptorWriteDescriptorSet.dstSet = m_descriptorSets[frameInFlight];
	texturesDescriptorWriteDescriptorSet.dstBinding = 2;
	texturesDescriptorWriteDescriptorSet.dstArrayElement = 0;
	texturesDescriptorWriteDescriptorSet.descriptorCount = static_cast<uint32_t>(texturesDescriptorImageInfos.size());
	texturesDescriptorWriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	texturesDescriptorWriteDescriptorSet.pImageInfo = texturesDescriptorImageInfos.data();
	texturesDescriptorWriteDescriptorSet.pBufferInfo = nullptr;
	texturesDescriptorWriteDescriptorSet.pTexelBufferView = nullptr;

	vkUpdateDescriptorSets(m_device, 1, &texturesDescriptorWriteDescriptorSet, 0, nullptr);
}

uint32_t RenderingEngine::loadModel(const std::string& modelFilePath) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	std::ifstream file(modelFilePath);

	// Ouverture du fichier
	if (!file.is_open()) {
		std::cout << "Impossible d'ouvrir le fichier de modele \"" + modelFilePath + "\"." << std::endl;
		exit(1);
	}

	std::vector<nml::vec3> positions;
	std::vector<nml::vec3> normals;
	std::vector<nml::vec2> uvs;

	std::unordered_map<std::string, uint32_t> uniqueVertices;

	std::string line;
	while (std::getline(file, line)) {
		// Les commentaires doivent etre ignores
		if (line[0] == '#') {
			continue;
		}

		// Tokens de la ligne
		std::vector<std::string> tokens;
		size_t spacePosition = 0;
		while ((spacePosition = line.find(' ')) != std::string::npos) {
			tokens.push_back(line.substr(0, spacePosition));
			line.erase(0, spacePosition + 1);
		}
		tokens.push_back(line);

		// Lecture des jetons
		// Position
		if (tokens[0] == "v") {
			positions.push_back({
				static_cast<float>(std::atof(tokens[1].c_str())),
				static_cast<float>(std::atof(tokens[2].c_str())),
				static_cast<float>(std::atof(tokens[3].c_str()))
				});
		}
		// Normale
		else if (tokens[0] == "vn") {
			normals.push_back({
				static_cast<float>(std::atof(tokens[1].c_str())),
				static_cast<float>(std::atof(tokens[2].c_str())),
				static_cast<float>(std::atof(tokens[3].c_str()))
				});
		}
		// Coordonnées de textures
		else if (tokens[0] == "vt") {
			uvs.push_back({
				static_cast<float>(std::atof(tokens[1].c_str())),
				static_cast<float>(std::atof(tokens[2].c_str()))
				});
		}
		// Face
		else if (tokens[0] == "f") {
			std::vector<uint32_t> tmpIndices;
			for (size_t i = 1; i < tokens.size(); i++) {
				Vertex vertex = {};

				std::string tmp = tokens[i];
				std::vector<std::string> valueIndices;
				size_t slashPosition = 0;
				while ((slashPosition = tmp.find('/')) != std::string::npos) {
					valueIndices.push_back(tmp.substr(0, slashPosition));
					tmp.erase(0, slashPosition + 1);
				}
				valueIndices.push_back(tmp);

				for (size_t j = 0; j < valueIndices.size(); j++) {
					if (valueIndices[j] != "") {
						// v/vt/vn
						// Indice de position
						if (j == 0) {
							vertex.position[0] = positions[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][0];
							vertex.position[1] = positions[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][1];
							vertex.position[2] = positions[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][2];
						}
						// Indice de coordonnées de texture
						else if (j == 1) {
							vertex.uv[0] = uvs[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][0];
							vertex.uv[1] = uvs[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][1];
						}
						// Indice de normale
						else if (j == 2) {
							vertex.normal[0] = normals[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][0];
							vertex.normal[1] = normals[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][1];
							vertex.normal[2] = normals[static_cast<size_t>(std::atoi(valueIndices[j].c_str())) - 1][2];
						}
					}
				}

				if (uniqueVertices.count(tokens[i]) == 0) {
					uniqueVertices[tokens[i]] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}
				tmpIndices.push_back(uniqueVertices[tokens[i]]);
			}

			// Une face peut etre un triangle ou un rectangle
			// Triangle
			if (tmpIndices.size() == 3) {
				indices.insert(indices.end(), std::make_move_iterator(tmpIndices.begin()), std::make_move_iterator(tmpIndices.end()));
			}
			// Rectangle
			else if (tmpIndices.size() == 4) {
				// Triangle 1
				indices.push_back(tmpIndices[0]);
				indices.push_back(tmpIndices[1]);
				indices.push_back(tmpIndices[2]);

				// Triangle 2
				indices.push_back(tmpIndices[0]);
				indices.push_back(tmpIndices[2]);
				indices.push_back(tmpIndices[3]);
			}
		}
	}

	// Fermeture du fichier
	file.close();

	// Ajout du maillage a la liste
	Mesh mesh;
	mesh.indexCount = static_cast<uint32_t>(indices.size());
	mesh.firstIndex = m_currentIndexOffset;
	mesh.vertexOffset = m_currentVertexOffset;
	m_meshes.push_back(mesh);

	// Creation du staging buffer
	VkBuffer vertexAndIndexStagingBuffer;
	VmaAllocation vertexAndIndexStagingBufferAllocation;

	VkBufferCreateInfo vertexAndIndexStagingBufferCreateInfo = {};
	vertexAndIndexStagingBufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	vertexAndIndexStagingBufferCreateInfo.pNext = nullptr;
	vertexAndIndexStagingBufferCreateInfo.flags = 0;
	vertexAndIndexStagingBufferCreateInfo.size = (vertices.size() * sizeof(Vertex)) + (indices.size() * sizeof(uint32_t));
	vertexAndIndexStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	vertexAndIndexStagingBufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	vertexAndIndexStagingBufferCreateInfo.queueFamilyIndexCount = 1;
	vertexAndIndexStagingBufferCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;

	VmaAllocationCreateInfo vertexAndIndexStagingBufferAllocationCreateInfo = {};
	vertexAndIndexStagingBufferAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
	vertexAndIndexStagingBufferAllocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
	VK_CHECK(vmaCreateBuffer(m_allocator, &vertexAndIndexStagingBufferCreateInfo, &vertexAndIndexStagingBufferAllocationCreateInfo, &vertexAndIndexStagingBuffer, &vertexAndIndexStagingBufferAllocation, nullptr));

	// Copie des donnees CPU vers le Staging Buffer
	void* data;

	VK_CHECK(vmaMapMemory(m_allocator, vertexAndIndexStagingBufferAllocation, &data));
	memcpy(data, vertices.data(), vertices.size() * sizeof(Vertex));
	memcpy(reinterpret_cast<char*>(data) + (vertices.size() * sizeof(Vertex)), indices.data(), indices.size() * sizeof(uint32_t));
	vmaUnmapMemory(m_allocator, vertexAndIndexStagingBufferAllocation);

	// Copie le Staging Buffer vers le Vertex Buffer et l'Index Buffer
	VkCommandPool buffersCopyCommandPool;

	VkCommandPoolCreateInfo buffersCopyCommandPoolCreateInfo = {};
	buffersCopyCommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	buffersCopyCommandPoolCreateInfo.pNext = nullptr;
	buffersCopyCommandPoolCreateInfo.flags = 0;
	buffersCopyCommandPoolCreateInfo.queueFamilyIndex = m_graphicsQueueFamilyIndex;
	VK_CHECK(vkCreateCommandPool(m_device, &buffersCopyCommandPoolCreateInfo, nullptr, &buffersCopyCommandPool));

	VkCommandBuffer buffersCopyCommandBuffer;

	VkCommandBufferAllocateInfo buffersCopyCommandBufferAllocateInfo = {};
	buffersCopyCommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	buffersCopyCommandBufferAllocateInfo.pNext = nullptr;
	buffersCopyCommandBufferAllocateInfo.commandPool = buffersCopyCommandPool;
	buffersCopyCommandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	buffersCopyCommandBufferAllocateInfo.commandBufferCount = 1;
	VK_CHECK(vkAllocateCommandBuffers(m_device, &buffersCopyCommandBufferAllocateInfo, &buffersCopyCommandBuffer));

	VkCommandBufferBeginInfo vertexAndIndexBuffersCopyBeginInfo = {};
	vertexAndIndexBuffersCopyBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	vertexAndIndexBuffersCopyBeginInfo.pNext = nullptr;
	vertexAndIndexBuffersCopyBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vertexAndIndexBuffersCopyBeginInfo.pInheritanceInfo = nullptr;
	VK_CHECK(vkBeginCommandBuffer(buffersCopyCommandBuffer, &vertexAndIndexBuffersCopyBeginInfo));

	VkBufferCopy vertexBufferCopy = {};
	vertexBufferCopy.srcOffset = 0;
	vertexBufferCopy.dstOffset = m_currentVertexOffset * sizeof(Vertex);
	vertexBufferCopy.size = vertices.size() * sizeof(Vertex);
	vkCmdCopyBuffer(buffersCopyCommandBuffer, vertexAndIndexStagingBuffer, m_vertexBuffer, 1, &vertexBufferCopy);

	VkBufferCopy indexBufferCopy = {};
	indexBufferCopy.srcOffset = vertices.size() * sizeof(Vertex);
	indexBufferCopy.dstOffset = m_currentIndexOffset * sizeof(uint32_t);
	indexBufferCopy.size = indices.size() * sizeof(uint32_t);
	vkCmdCopyBuffer(buffersCopyCommandBuffer, vertexAndIndexStagingBuffer, m_indexBuffer, 1, &indexBufferCopy);

	VK_CHECK(vkEndCommandBuffer(buffersCopyCommandBuffer));

	VkFence buffersCopyFence;

	VkFenceCreateInfo buffersCopyFenceCreateInfo = {};
	buffersCopyFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	buffersCopyFenceCreateInfo.pNext = nullptr;
	buffersCopyFenceCreateInfo.flags = 0;
	VK_CHECK(vkCreateFence(m_device, &buffersCopyFenceCreateInfo, nullptr, &buffersCopyFence));

	VkSubmitInfo buffersCopySubmitInfo = {};
	buffersCopySubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	buffersCopySubmitInfo.pNext = nullptr;
	buffersCopySubmitInfo.waitSemaphoreCount = 0;
	buffersCopySubmitInfo.pWaitSemaphores = nullptr;
	buffersCopySubmitInfo.pWaitDstStageMask = nullptr;
	buffersCopySubmitInfo.commandBufferCount = 1;
	buffersCopySubmitInfo.pCommandBuffers = &buffersCopyCommandBuffer;
	buffersCopySubmitInfo.signalSemaphoreCount = 0;
	buffersCopySubmitInfo.pSignalSemaphores = nullptr;
	VK_CHECK(vkQueueSubmit(m_graphicsQueue, 1, &buffersCopySubmitInfo, buffersCopyFence));
	VK_CHECK(vkWaitForFences(m_device, 1, &buffersCopyFence, VK_TRUE, std::numeric_limits<uint64_t>::max()));

	// Destruction des ressources utilisees pour la copie des buffers
	vkDestroyFence(m_device, buffersCopyFence, nullptr);
	vkDestroyCommandPool(m_device, buffersCopyCommandPool, nullptr);
	vmaDestroyBuffer(m_allocator, vertexAndIndexStagingBuffer, vertexAndIndexStagingBufferAllocation);

	// Decalage des vertices et des indices pour le prochain maillage
	m_currentVertexOffset += static_cast<int32_t>(vertices.size());
	m_currentIndexOffset += static_cast<uint32_t>(indices.size());

	return static_cast<uint32_t>(m_meshes.size() - 1);
}

uint32_t RenderingEngine::findMipLevels(uint32_t width, uint32_t height) {
	return static_cast<uint32_t>(std::floor(std::log2(std::min(width, height)) + 1));
}

uint32_t RenderingEngine::loadTexture(const std::string& textureFilePath) {
	int width;
	int height;
	int texChannels;

	stbi_uc* pixels = stbi_load(textureFilePath.c_str(), &width, &height, &texChannels, STBI_rgb_alpha);
	if (!pixels) {
		std::cout << "Une erreur a eu lieu lors de la lecture de l\'image \"" + textureFilePath + "\"." << std::endl;
		exit(1);
	}

	// Creation de l'image de la texture
	VkImage textureImage;
	VmaAllocation textureImageAllocation;

	VkImageCreateInfo textureImageCreateInfo = {};
	textureImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	textureImageCreateInfo.pNext = nullptr;
	textureImageCreateInfo.flags = 0;
	textureImageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	textureImageCreateInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	textureImageCreateInfo.extent.width = static_cast<uint32_t>(width);
	textureImageCreateInfo.extent.height = static_cast<uint32_t>(height);
	textureImageCreateInfo.extent.depth = 1;
	textureImageCreateInfo.mipLevels = findMipLevels(textureImageCreateInfo.extent.width, textureImageCreateInfo.extent.height);
	textureImageCreateInfo.arrayLayers = 1;
	textureImageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	textureImageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	textureImageCreateInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	textureImageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	textureImageCreateInfo.queueFamilyIndexCount = 1;
	textureImageCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;
	textureImageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VmaAllocationCreateInfo textureImageAllocationCreateInfo = {};
	textureImageAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;

	VK_CHECK(vmaCreateImage(m_allocator, &textureImageCreateInfo, &textureImageAllocationCreateInfo, &textureImage, &textureImageAllocation, nullptr));

	// Creation de la vue de l'image de la texture
	VkImageView textureImageView;

	VkImageViewCreateInfo textureImageViewCreateInfo = {};
	textureImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	textureImageViewCreateInfo.pNext = nullptr;
	textureImageViewCreateInfo.flags = 0;
	textureImageViewCreateInfo.image = textureImage;
	textureImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	textureImageViewCreateInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
	textureImageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_R;
	textureImageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_G;
	textureImageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_B;
	textureImageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_A;
	textureImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	textureImageViewCreateInfo.subresourceRange.baseMipLevel = 0;
	textureImageViewCreateInfo.subresourceRange.levelCount = textureImageCreateInfo.mipLevels;
	textureImageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	textureImageViewCreateInfo.subresourceRange.layerCount = 1;
	VK_CHECK(vkCreateImageView(m_device, &textureImageViewCreateInfo, nullptr, &textureImageView));

	// Creation du staging buffer
	VkBuffer textureStagingBuffer;
	VmaAllocation textureStagingBufferAllocation;

	VkBufferCreateInfo textureStagingBufferCreateInfo = {};
	textureStagingBufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	textureStagingBufferCreateInfo.pNext = nullptr;
	textureStagingBufferCreateInfo.flags = 0;
	textureStagingBufferCreateInfo.size = static_cast<size_t>(width) * static_cast<size_t>(width) * 4;
	textureStagingBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	textureStagingBufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	textureStagingBufferCreateInfo.queueFamilyIndexCount = 1;
	textureStagingBufferCreateInfo.pQueueFamilyIndices = &m_graphicsQueueFamilyIndex;

	VmaAllocationCreateInfo textureStagingBufferAllocationCreateInfo = {};
	textureStagingBufferAllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
	textureStagingBufferAllocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
	VK_CHECK(vmaCreateBuffer(m_allocator, &textureStagingBufferCreateInfo, &textureStagingBufferAllocationCreateInfo, &textureStagingBuffer, &textureStagingBufferAllocation, nullptr));

	void* data;
	VK_CHECK(vmaMapMemory(m_allocator, textureStagingBufferAllocation, &data));
	memcpy(data, pixels, static_cast<size_t>(width) * static_cast<size_t>(height) * 4);
	vmaUnmapMemory(m_allocator, textureStagingBufferAllocation);

	stbi_image_free(pixels);

	// Copie du staging buffer et generation des mipmaps
	VkCommandPool createTextureCommandPool;

	VkCommandPoolCreateInfo createTextureCommandPoolCreateInfo = {};
	createTextureCommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createTextureCommandPoolCreateInfo.pNext = nullptr;
	createTextureCommandPoolCreateInfo.flags = 0;
	createTextureCommandPoolCreateInfo.queueFamilyIndex = m_graphicsQueueFamilyIndex;
	VK_CHECK(vkCreateCommandPool(m_device, &createTextureCommandPoolCreateInfo, nullptr, &createTextureCommandPool));

	VkCommandBuffer createTextureCommandBuffer;

	VkCommandBufferAllocateInfo createTextureCommandBufferAllocateInfo = {};
	createTextureCommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	createTextureCommandBufferAllocateInfo.pNext = nullptr;
	createTextureCommandBufferAllocateInfo.commandPool = createTextureCommandPool;
	createTextureCommandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	createTextureCommandBufferAllocateInfo.commandBufferCount = 1;
	VK_CHECK(vkAllocateCommandBuffers(m_device, &createTextureCommandBufferAllocateInfo, &createTextureCommandBuffer));

	VkCommandBufferBeginInfo createTextureCommandBufferBeginInfo = {};
	createTextureCommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	createTextureCommandBufferBeginInfo.pNext = nullptr;
	createTextureCommandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	createTextureCommandBufferBeginInfo.pInheritanceInfo = nullptr;
	VK_CHECK(vkBeginCommandBuffer(createTextureCommandBuffer, &createTextureCommandBufferBeginInfo));

	VkImageMemoryBarrier2 undefinedToTransferDstOptimalImageMemoryBarrier = {};
	undefinedToTransferDstOptimalImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	undefinedToTransferDstOptimalImageMemoryBarrier.pNext = nullptr;
	undefinedToTransferDstOptimalImageMemoryBarrier.srcStageMask = VK_PIPELINE_STAGE_2_NONE;
	undefinedToTransferDstOptimalImageMemoryBarrier.srcAccessMask = 0;
	undefinedToTransferDstOptimalImageMemoryBarrier.dstStageMask = VK_PIPELINE_STAGE_2_COPY_BIT;
	undefinedToTransferDstOptimalImageMemoryBarrier.dstAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT;
	undefinedToTransferDstOptimalImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	undefinedToTransferDstOptimalImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	undefinedToTransferDstOptimalImageMemoryBarrier.srcQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	undefinedToTransferDstOptimalImageMemoryBarrier.dstQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	undefinedToTransferDstOptimalImageMemoryBarrier.image = textureImage;
	undefinedToTransferDstOptimalImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	undefinedToTransferDstOptimalImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
	undefinedToTransferDstOptimalImageMemoryBarrier.subresourceRange.levelCount = textureImageCreateInfo.mipLevels;
	undefinedToTransferDstOptimalImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
	undefinedToTransferDstOptimalImageMemoryBarrier.subresourceRange.layerCount = 1;

	VkDependencyInfo undefinedToTransferDstOptimalDependencyInfo = {};
	undefinedToTransferDstOptimalDependencyInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	undefinedToTransferDstOptimalDependencyInfo.pNext = nullptr;
	undefinedToTransferDstOptimalDependencyInfo.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
	undefinedToTransferDstOptimalDependencyInfo.memoryBarrierCount = 0;
	undefinedToTransferDstOptimalDependencyInfo.pMemoryBarriers = nullptr;
	undefinedToTransferDstOptimalDependencyInfo.bufferMemoryBarrierCount = 0;
	undefinedToTransferDstOptimalDependencyInfo.pBufferMemoryBarriers = nullptr;
	undefinedToTransferDstOptimalDependencyInfo.imageMemoryBarrierCount = 1;
	undefinedToTransferDstOptimalDependencyInfo.pImageMemoryBarriers = &undefinedToTransferDstOptimalImageMemoryBarrier;
	m_vkCmdPipelineBarrier2KHR(createTextureCommandBuffer, &undefinedToTransferDstOptimalDependencyInfo);

	VkBufferImageCopy textureBufferCopy = {};
	textureBufferCopy.bufferOffset = 0;
	textureBufferCopy.bufferRowLength = 0;
	textureBufferCopy.bufferImageHeight = 0;
	textureBufferCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	textureBufferCopy.imageSubresource.mipLevel = 0;
	textureBufferCopy.imageSubresource.baseArrayLayer = 0;
	textureBufferCopy.imageSubresource.layerCount = 1;
	textureBufferCopy.imageOffset.x = 0;
	textureBufferCopy.imageOffset.y = 0;
	textureBufferCopy.imageOffset.z = 0;
	textureBufferCopy.imageExtent.width = static_cast<uint32_t>(width);
	textureBufferCopy.imageExtent.height = static_cast<uint32_t>(height);
	textureBufferCopy.imageExtent.depth = 1;
	vkCmdCopyBufferToImage(createTextureCommandBuffer, textureStagingBuffer, textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &textureBufferCopy);

	VkImageMemoryBarrier2 mipMapGenerationImageMemoryBarrier = {};
	mipMapGenerationImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	mipMapGenerationImageMemoryBarrier.pNext = nullptr;
	mipMapGenerationImageMemoryBarrier.srcQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	mipMapGenerationImageMemoryBarrier.dstQueueFamilyIndex = m_graphicsQueueFamilyIndex;
	mipMapGenerationImageMemoryBarrier.image = textureImage;
	mipMapGenerationImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	mipMapGenerationImageMemoryBarrier.subresourceRange.levelCount = 1;
	mipMapGenerationImageMemoryBarrier.subresourceRange.baseArrayLayer = 0;
	mipMapGenerationImageMemoryBarrier.subresourceRange.layerCount = 1;

	uint32_t mipWidth = textureImageCreateInfo.extent.width;
	uint32_t mipHeight = textureImageCreateInfo.extent.height;
	for (size_t i = 1; i < textureImageCreateInfo.mipLevels; i++) {
		mipMapGenerationImageMemoryBarrier.srcStageMask = VK_PIPELINE_STAGE_2_COPY_BIT;
		mipMapGenerationImageMemoryBarrier.srcAccessMask = VK_ACCESS_2_TRANSFER_WRITE_BIT;
		mipMapGenerationImageMemoryBarrier.dstStageMask = VK_PIPELINE_STAGE_2_COPY_BIT;
		mipMapGenerationImageMemoryBarrier.dstAccessMask = VK_ACCESS_2_TRANSFER_READ_BIT;
		mipMapGenerationImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		mipMapGenerationImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		mipMapGenerationImageMemoryBarrier.subresourceRange.baseMipLevel = static_cast<uint32_t>(i) - 1;

		VkDependencyInfo mipMapGenerationDependencyInfo = {};
		mipMapGenerationDependencyInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
		mipMapGenerationDependencyInfo.pNext = nullptr;
		mipMapGenerationDependencyInfo.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
		mipMapGenerationDependencyInfo.memoryBarrierCount = 0;
		mipMapGenerationDependencyInfo.pMemoryBarriers = nullptr;
		mipMapGenerationDependencyInfo.bufferMemoryBarrierCount = 0;
		mipMapGenerationDependencyInfo.pBufferMemoryBarriers = nullptr;
		mipMapGenerationDependencyInfo.imageMemoryBarrierCount = 1;
		mipMapGenerationDependencyInfo.pImageMemoryBarriers = &mipMapGenerationImageMemoryBarrier;
		m_vkCmdPipelineBarrier2KHR(createTextureCommandBuffer, &mipMapGenerationDependencyInfo);

		VkImageBlit imageBlit = {};
		imageBlit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageBlit.srcSubresource.mipLevel = static_cast<uint32_t>(i) - 1;
		imageBlit.srcSubresource.baseArrayLayer = 0;
		imageBlit.srcSubresource.layerCount = 1;
		imageBlit.srcOffsets[0].x = 0;
		imageBlit.srcOffsets[0].y = 0;
		imageBlit.srcOffsets[0].z = 0;
		imageBlit.srcOffsets[1].x = mipWidth;
		imageBlit.srcOffsets[1].y = mipHeight;
		imageBlit.srcOffsets[1].z = 1;
		imageBlit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageBlit.dstSubresource.mipLevel = static_cast<uint32_t>(i);
		imageBlit.dstSubresource.baseArrayLayer = 0;
		imageBlit.dstSubresource.layerCount = 1;
		imageBlit.dstOffsets[0].x = 0;
		imageBlit.dstOffsets[0].y = 0;
		imageBlit.dstOffsets[0].z = 0;
		imageBlit.dstOffsets[1].x = mipWidth > 1 ? mipWidth / 2 : 1;
		imageBlit.dstOffsets[1].y = mipHeight > 1 ? mipHeight / 2 : 1;
		imageBlit.dstOffsets[1].z = 1;
		vkCmdBlitImage(createTextureCommandBuffer, textureImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, textureImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageBlit, VK_FILTER_LINEAR);

		mipMapGenerationImageMemoryBarrier.srcStageMask = VK_PIPELINE_STAGE_2_COPY_BIT;
		mipMapGenerationImageMemoryBarrier.srcAccessMask = VK_ACCESS_2_TRANSFER_READ_BIT;
		mipMapGenerationImageMemoryBarrier.dstStageMask = VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT;
		mipMapGenerationImageMemoryBarrier.dstAccessMask = VK_ACCESS_2_SHADER_SAMPLED_READ_BIT;
		mipMapGenerationImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		mipMapGenerationImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		mipMapGenerationDependencyInfo.pImageMemoryBarriers = &mipMapGenerationImageMemoryBarrier;
		m_vkCmdPipelineBarrier2KHR(createTextureCommandBuffer, &mipMapGenerationDependencyInfo);

		mipWidth = mipWidth > 1 ? mipWidth / 2 : 1;
		mipHeight = mipHeight > 1 ? mipHeight / 2 : 1;
	}

	VK_CHECK(vkEndCommandBuffer(createTextureCommandBuffer));

	VkFence buffersCopyFence;

	VkFenceCreateInfo buffersCopyFenceCreateInfo = {};
	buffersCopyFenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	buffersCopyFenceCreateInfo.pNext = nullptr;
	buffersCopyFenceCreateInfo.flags = 0;
	VK_CHECK(vkCreateFence(m_device, &buffersCopyFenceCreateInfo, nullptr, &buffersCopyFence));

	VkSubmitInfo buffersCopySubmitInfo = {};
	buffersCopySubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	buffersCopySubmitInfo.pNext = nullptr;
	buffersCopySubmitInfo.waitSemaphoreCount = 0;
	buffersCopySubmitInfo.pWaitSemaphores = nullptr;
	buffersCopySubmitInfo.pWaitDstStageMask = nullptr;
	buffersCopySubmitInfo.commandBufferCount = 1;
	buffersCopySubmitInfo.pCommandBuffers = &createTextureCommandBuffer;
	buffersCopySubmitInfo.signalSemaphoreCount = 0;
	buffersCopySubmitInfo.pSignalSemaphores = nullptr;
	VK_CHECK(vkQueueSubmit(m_graphicsQueue, 1, &buffersCopySubmitInfo, buffersCopyFence));
	VK_CHECK(vkWaitForFences(m_device, 1, &buffersCopyFence, VK_TRUE, std::numeric_limits<uint64_t>::max()));

	vkDestroyFence(m_device, buffersCopyFence, nullptr);
	vkDestroyCommandPool(m_device, createTextureCommandPool, nullptr);
	vmaDestroyBuffer(m_allocator, textureStagingBuffer, textureStagingBufferAllocation);

	m_textureImages.push_back(textureImage);
	m_textureImageAllocations.push_back(textureImageAllocation);
	m_textureImageViews.push_back(textureImageView);

	// Les descriptor sets doivent etre mis a jour
	for (uint32_t i = 0; i < m_framesInFlight; i++) {
		m_descriptorSetsNeedUpdate[i] = true;
	}

	return static_cast<uint32_t>(m_textureImages.size() - 1);
}

void RenderingEngine::createScene() {
	uint32_t cubeMesh = loadModel("../models/cube.obj");
	uint32_t sphereMesh = loadModel("../models/sphere.obj");

	uint32_t dustTexture = loadTexture("../models/dust.jpg");
	uint32_t groundTexture = loadTexture("../models/ground.jpg");

	Object object1;

	object1.index = m_objectIndex++; // Indice 0

	object1.position = nml::vec3(-2.0f, 0.0f, 0.0f);
	object1.rotation = nml::vec3(0.0f, 0.0f, 0.0f);
	object1.scale = nml::vec3(1.0f, 1.0f, 1.0f);

	object1.meshIndex = cubeMesh;
	object1.textureIndex = groundTexture;

	m_objects.push_back(object1);

	Object object2;

	object2.index = m_objectIndex++; // Indice 1

	object2.position = nml::vec3(2.0f, 0.0f, 0.0f);
	object2.rotation = nml::vec3(0.0f, 0.0f, 0.0f);
	object2.scale = nml::vec3(1.0f, 1.0f, 1.0f);

	object2.meshIndex = sphereMesh;
	object2.textureIndex = dustTexture;

	m_objects.push_back(object2);
}
