#include "vulkan_context.hpp"

#include "containers/feasy_string.hpp"
#include "core/logger.hpp"
#include "containers/feasy_darray.hpp"
#include <SDL_vulkan.h>
#include <iostream>

#ifdef DEBUG
constexpr feasy::b8 ENABLE_VALIDATION_LAYERS = true;
#else
constexpr feasy::b8 ENABLE_VALIDATION_LAYERS = false;
#endif

const feasy::DArray<const char *> validation_layers = {
	"VK_LAYER_KHRONOS_validation"};

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
	if constexpr (ENABLE_VALIDATION_LAYERS)
	{
		if (!checkValidationLayerSupport())
		{
			FEASY_LOG_FATAL("The validation layers requested, are not visible");
		}
	}
	FEASY_LOG_INFO("Create Vulkan API Instance...");

	VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
	appInfo.pApplicationName = "Feasy Game";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Feasy Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_VERSION_1_3;

	VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
	createInfo.pApplicationInfo = &appInfo;

	// layers:
	if constexpr (ENABLE_VALIDATION_LAYERS)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
		createInfo.ppEnabledLayerNames = validation_layers.data();
	}

	// extensions:
	DArray<const char *> extensions = getRequredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	// create the instance
	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
		FEASY_LOG_FATAL("Failed to create VkInstance.");
	else
		FEASY_LOG_DEBUG("Initialized VkInstance.");
}

void feasy::VulkanContext::pickPhysicalDevice()
{
	FEASY_LOG_INFO("Pick Physical GPU...");
}

feasy::DArray<const char *> feasy::VulkanContext::getRequredExtensions()
{
	// SDL extension
	SDL_Window *window = reinterpret_cast<SDL_Window *>(m_platformState->handle);
	u32 sdlExtensionCount = 0;
	SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, nullptr);

	DArray<const char *> sdlExtensions(sdlExtensionCount);

	if (SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, sdlExtensions.data()) == SDL_FALSE)
		FEASY_LOG_FATAL("Failed to load SDL Instance Extensions for Vulkan API.");
	else
		FEASY_LOG_DEBUG("Loaded SDL Extensions for Vulkan API.");

	// extensions:
	DArray<const char *> extensions(std::move(sdlExtensions));

	if constexpr (ENABLE_VALIDATION_LAYERS)
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

feasy::b8 feasy::VulkanContext::checkValidationLayerSupport()
{
	u32 layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	DArray<VkLayerProperties> availableProperties(layerCount);
	if (vkEnumerateInstanceLayerProperties(&layerCount, availableProperties.data()) != VK_SUCCESS)
	{
		FEASY_LOG_ERROR("Could not enumerate over Vulkan instance layer properties.");
	}

#ifdef DEBUG
	for (auto layerProperties : availableProperties)
	{
		FEASY_LOG_DEBUG("Vulkan Layer found: %s", layerProperties.layerName);
	}
#endif

	for (const char *layerName : validation_layers)
	{
		b8 layerFound = false;

		for (const auto &layerProperties : availableProperties)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			FEASY_LOG_ERROR("validation layer name not found: %s", layerName);
			return false;
		}
	}

	return true;
}