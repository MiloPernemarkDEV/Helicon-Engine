#include "Renderer.h"
#include <stdexcept>


void Renderer::createVkInstance() 
{
    if (enableValidationLayers && !validationHelper_.checkValidationLayerSupport()) 
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{}; 
    populateInstanceCreateInfo(createInfo, appInfo, debugCreateInfo);

    if (vkCreateInstance(&createInfo, nullptr, &vkInstance_) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }
}

bool Renderer::Initialize(HWND hWnd) 
{
    createVkInstance();

    validationHelper_.setupDebugMessenger(vkInstance_, debugMessenger_);

    return true;
}

void Renderer::Shutdown() 
{

    deviceHelper_.clear(device_);
    validationHelper_.clear(vkInstance_, debugMessenger_);
    clearVkInstance();
}

std::unique_ptr<IRenderer> CreateVulkanRend() 
{
    return std::make_unique<Renderer>();
}

void Renderer::populateInstanceCreateInfo(
    VkInstanceCreateInfo& createInfo,
    VkApplicationInfo& appInfo,
    VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo)
{

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    extensions_ = validationHelper_.getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions_.size());
    createInfo.ppEnabledExtensionNames = extensions_.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        validationHelper_.populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }
}

void Renderer::clearVkInstance()
{
    if (vkInstance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(vkInstance_, nullptr);
    }
}
