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

void Device::createLogicalDevice(VkPhysicalDevice physicalDevice)
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}
}

bool Device::isDeviceSuitable(VkPhysicalDevice device) 
{
	QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}

void Device::clear(VkDevice& device)
{
	vkDestroyDevice(device, nullptr);
}

QueueFamilyIndices Device::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	std::uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			indices.graphicsFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		i++;
	}

	return indices;
}