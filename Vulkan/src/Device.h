#pragma once 

#include <vulkan/vulkan.h>

class Device {
public:
	void pickPhysicalDevice(VkPhysicalDevice physicalDevice, VkInstance instance);
	bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkInstance instance);
private:

};