#pragma once

#include <vulkan/vulkan.h>
#include <cstdint>

class PhysicalDevice {
public:
	
	void setup(VkInstance instance);
	void destroy();

	VkPhysicalDevice getPhysicalDevice() const { return physicalDevice_; }
	bool isDeviceSuitable(VkPhysicalDevice device);

private:
	VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;


};