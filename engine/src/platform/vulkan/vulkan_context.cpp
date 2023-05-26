#include "vulkan_context.hpp"

#include "containers/feasy_string.hpp"
#include "core/logger.hpp"
#include "containers/feasy_darray.hpp"
#include <SDL_vulkan.h>

feasy::VulkanContext::VulkanContext(const Ref<PlatformState> &platformState)
{
	m_platformState = platformState;
}

void feasy::VulkanContext::init()
{
	createInstance();
	pickPhysicalDevice();
}

void feasy::VulkanContext::createInstance()
{
	FEASY_LOG_INFO("Create Vulkan API Instance...");

	VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
	appInfo.pApplicationName = "Feasy Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Feasy Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_VERSION_1_2;

	VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
	createInfo.pApplicationInfo = &appInfo;

	// extensions:
	SDL_Window *window = reinterpret_cast<SDL_Window *>(m_platformState->handle);
	u32 sdlExtensionCount = 0;
	SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, nullptr);
	const char **sdlExtensions = new const char *[sdlExtensionCount];
	// DArray<String> sdlExtensions(sdlExtensionCount); // TODO: extend this to make that possible

	if (SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, sdlExtensions) == SDL_FALSE)
		FEASY_LOG_FATAL("Failed to load SDL Instance Extensions for Vulkan API.");
	else
		FEASY_LOG_DEBUG("Loaded SDL Extensions for Vulkan API.");

	createInfo.enabledExtensionCount = sdlExtensionCount;
	createInfo.ppEnabledExtensionNames = sdlExtensions;

	// create the instance
	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
		FEASY_LOG_FATAL("Failed to create VkInstace.");
	else
		FEASY_LOG_DEBUG("Initialized VkInstanece.");
}

void feasy::VulkanContext::pickPhysicalDevice()
{
	FEASY_LOG_INFO("Pick Physical GPU...");
}
