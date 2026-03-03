#include "Device.h"

#include <stdexcept>
#include <vector>

void Device::pickPhysicalDevice(VkPhysicalDevice physicalDevice, VkInstance instance)
{
	uint32_t device_count = 0;

	// Makes sure there is a GPU that supports Vulkan 
	vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

	if (device_count == 0) 
	{
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	// Makes sure the devices are suitable for our app 
	// What makes a device suitable can be changed 
	// We look for a dedicated GPU with support for geometry shaders 
	// Some GPUs are not for graphics... yeah want to avoid that 
	std::vector<VkPhysicalDevice> devices(device_count);
	vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) 
	{
		throw std::runtime_error("failed to find suitable GPU!");
	}
}

bool Device::isDeviceSuitable(VkPhysicalDevice device) 
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	// If we want to we can turn this into a setting later letting the user decide what GPU the game should run on 
	// One of multiple opportunities Vulkan gives us.
	return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		deviceFeatures.geometryShader;
}