#pragma once

#include "feasy.hpp"
#include "core/ref.hpp"
#include "platform/platform.hpp"
#include "containers/feasy_darray.hpp"
#include <vulkan/vulkan.h>

namespace feasy
{
	class VulkanContext
	{
	public:
		VulkanContext(const Ref<PlatformState> &platformState);
		void init();

	private:
		// functions (1rst level)
		void createInstance();
		void pickPhysicalDevice();

		// helper functions (2nd level)
		feasy::b8 checkValidationLayerSupport();
		DArray<const char *> getRequredExtensions();

		Ref<PlatformState> m_platformState;
		VkInstance m_instance;
		VkPhysicalDevice m_physicalDevice;
	};
}