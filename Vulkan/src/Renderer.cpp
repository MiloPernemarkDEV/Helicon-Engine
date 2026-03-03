#include "Renderer.h"
#include <stdexcept>


void Renderer::createVkInstance() 
{
    if (enableValidationLayers && !m_validationHelper.checkValidationLayerSupport()) 
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{}; 
    populateInstanceCreateInfo(createInfo, appInfo, debugCreateInfo);

    if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS) 
    {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }
}

bool Renderer::Initialize(HWND hWnd) 
{
    createVkInstance();

    m_validationHelper.setupDebugMessenger(m_vkInstance, m_debugMessenger);

    return true;
}

void Renderer::Shutdown() 
{

    m_validationHelper.clear(m_vkInstance, m_debugMessenger);

    clearVkInstance();
  
}

IRenderer* hcCreateRenderer() 
{
    return new Renderer();
}

void Renderer::clearVkInstance() 
{
    if (m_vkInstance != VK_NULL_HANDLE) {
        vkDestroyInstance(m_vkInstance, nullptr);
    }
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

    std::vector<const char*> extensions = m_validationHelper.getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        m_validationHelper.populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugCreateInfo);
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }
}
