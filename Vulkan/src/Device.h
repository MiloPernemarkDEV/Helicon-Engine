#pragma once 

#include <vulkan/vulkan.h>
#include <optional>
#include "Validation.h"


struct QueueFamilyIndices {
public:
	std::optional<std::uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class Device {
public:
	void pickPhysicalDevice(VkPhysicalDevice physicalDevice, VkInstance instance);
	void createLogicalDevice(VkPhysicalDevice physicalDevice);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice physicalDevice);
	void clear(VkDevice& device);
private:
	

};