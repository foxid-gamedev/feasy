#pragma once

#include "feasy.hpp"
#include "core/ref.hpp"
#include "platform/platform.hpp"

#include <vulkan/vulkan.h>

namespace feasy
{
	class VulkanContext
	{
	public:
		VulkanContext(const Ref<PlatformState> &platformState);
		void init();

	private:
		void createInstance();
		void pickPhysicalDevice();

		Ref<PlatformState> m_platformState;
		VkInstance m_instance;
		VkPhysicalDevice m_physicalDevice;
	};
}