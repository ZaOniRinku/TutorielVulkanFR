#pragma once
#include "../external/glfw/include/GLFW/glfw3.h"
#if defined(TUTORIEL_VK_OS_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(TUTORIEL_VK_OS_LINUX)
#define VK_USE_PLATFORM_XLIB_KHR
#endif
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <string>

#define TUTORIEL_VK_CHECK(f) \
	do { \
		int64_t check = f; \
		if (check) { \
			std::cout << "Vulkan Error.\nError code: " << check << "\nFile: " << __FILE__ << "\nFunction: " << #f << "\nLine: " << __LINE__ << std::endl; \
			exit(1); \
		} \
	} while(0)

enum struct ShaderType {
	Vertex,
	TessellationControl,
	TessellationEvaluation,
	Geometry,
	Fragment
};

class HelloTriangle {
public:
	void init();
	void update();
	void destroy();

	bool shouldClose();

private:
	bool explicitLayerAvailable(const char* layerName);
	bool instanceExtensionAvailable(const char* extensionName);
	bool deviceExtensionAvailable(const char* extensionName);
	void createGraphicsPipeline();
	std::string readBinaryFile(const std::string& filePath);
	std::string readAsciiFile(const std::string& filePath);
	std::vector<uint32_t> compileShaderFile(const std::string& shaderCode, ShaderType shaderType);
	void createSwapchain(VkSwapchainKHR oldSwapchain);

private:
	VkInstance m_instance; // Le prefixe m_ sert a differencier les attributs des classes aux variables locales
	VkDebugUtilsMessengerEXT m_debugMessenger;

	GLFWwindow* m_window;
	VkSurfaceKHR m_surface;
#if defined(TUTORIEL_VK_OS_LINUX)
	Display* m_display;
#endif

	VkPhysicalDevice m_physicalDevice;
	VkDevice m_device;
	uint32_t m_graphicsQueueFamilyIndex;
	VkQueue m_graphicsQueue;

	VkSwapchainKHR m_swapchain;
	uint32_t m_swapchainImageCount;
	VkFormat m_swapchainFormat;
	std::vector<VkImage> m_swapchainImages;
	std::vector<VkImageView> m_swapchainImageViews;

	VkPipeline m_graphicsPipeline;
	VkPipelineLayout m_graphicsPipelineLayout;

	VkViewport m_viewport;
	VkRect2D m_scissor;

	bool m_glslangInitialized = false;

	uint32_t m_framesInFlight = 2;
	uint32_t m_currentFrameInFlight = 0;

	std::vector<VkCommandPool> m_renderingCommandPools;
	std::vector<VkCommandBuffer> m_renderingCommandBuffers;

	std::vector<VkFence> m_fences;
	std::vector<VkSemaphore> m_acquireCompletedSemaphores;
	std::vector<VkSemaphore> m_renderCompletedSemaphores;

	PFN_vkCmdBeginRenderingKHR m_vkCmdBeginRenderingKHR;
	PFN_vkCmdEndRenderingKHR m_vkCmdEndRenderingKHR;
	PFN_vkCmdPipelineBarrier2KHR m_vkCmdPipelineBarrier2KHR;
};