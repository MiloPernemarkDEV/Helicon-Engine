#pragma once

#include <vulkan/vulkan.h>
#include "Instance.h"
#include <cstdint>

class PhysicalDevice {
public:
	PhysicalDevice() = default;
	~PhysicalDevice() = default;

	void setup();
	void destroy();

	VkPhysicalDevice getPhysicalDevice() const { return physicalDevice_; }

private:
	VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
	Instance* instance_;
};