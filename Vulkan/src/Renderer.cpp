#include "Renderer.h"
#include <stdexcept>


void Renderer::createVkInstance() 
{
    if (enableValidationLayers && !validationHelper.checkValidationLayerSupport()) 
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{}; 
    populateInstanceCreateInfo(createInfo, appInfo, debugCreateInfo);

    if (vkCreateInstance(&createInfo, nullptr, &handles.vkInstance_) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }
}

bool Renderer::Initialize(HWND hWnd, HINSTANCE hInstance) 
{
    createVkInstance();
    validationHelper.setupDebugMessenger(handles.vkInstance_, handles.debugMessenger_);
    deviceHelper.CreateWin32WindowSurface(handles.vkInstance_, hWnd, hInstance, handles.surface_);
    deviceHelper.pickPhysicalDevice(handles.vkInstance_, handles.physicalDevice_);
    deviceHelper.createLogicalDevice(handles.physicalDevice_, handles.device_, handles.graphicsQueue_);
    

    return true;
}

void Renderer::Shutdown() 
{

    deviceHelper.clear(handles.device_);
    validationHelper.clear(handles.vkInstance_, handles.debugMessenger_);
    deviceHelper.destroySurface(handles.vkInstance_, handles.surface_);
    clearVkInstance();
}

std::unique_ptr<IRenderer> CreateVulkanRenderer() 
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

    extensions_ = validationHelper.getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions_.size());
    createInfo.ppEnabledExtensionNames = extensions_.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        validationHelper.populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }
}

void Renderer::clearVkInstance()
{
    if (handles.vkInstance_ != VK_NULL_HANDLE) {
        vkDestroyInstance(handles.vkInstance_, nullptr);
    }
}
