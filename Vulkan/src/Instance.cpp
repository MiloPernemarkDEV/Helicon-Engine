#include "Instance.h"

Instance::Instance(Validation& validation, const std::vector<const char*>& extensions)
    : validation_(&validation), extensions_(extensions), layers_(validation.getValidationlayers())
{
}

void Instance::setup() {
    if (enableValidationLayers && !validation_->checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    populateInstanceCreateInfo(createInfo, appInfo, debugCreateInfo);

    if (enableValidationLayers) {
        validation_->populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }


    if (vkCreateInstance(&createInfo, nullptr, &instance_) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }
}

void Instance::destroy()
{
    if (instance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(instance_, nullptr);
    }
}

void Instance::populateInstanceCreateInfo(
    VkInstanceCreateInfo& createInfo,
    VkApplicationInfo& appInfo,
    VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo) 
{
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "MyApp";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "HeliconEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (enableValidationLayers) {
        const auto& layers = validation_->getValidationlayers();
        createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        createInfo.ppEnabledLayerNames = layers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }

    if (extensions_.empty()) {
        throw std::runtime_error("Instance extensions list is empty!");
    }

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions_.size());
    createInfo.ppEnabledExtensionNames = extensions_.data();
    createInfo.pNext = nullptr;
}

