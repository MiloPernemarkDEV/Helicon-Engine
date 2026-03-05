#pragma once 

#include <vulkan/vulkan.h>
#include <optional>
#include "Validation.h"
#include "HcWin32Window.h"
#include <vulkan/vulkan_win32.h>


struct QueueFamilyIndices {
public:
	std::optional<std::uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class Device {
public:
	void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice physicalDevice);
	void createLogicalDevice(VkPhysicalDevice physicalDevice, VkDevice device, VkQueue graphicsQueue);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice physicalDevice);
	void clear(VkDevice& device);
	VkSurfaceKHR CreateWin32WindowSurface(VkInstance instance, HWND hWnd, HINSTANCE, VkSurfaceKHR surface);
	void destroySurface(VkInstance& instance, VkSurfaceKHR surface);
private:
	
	

};