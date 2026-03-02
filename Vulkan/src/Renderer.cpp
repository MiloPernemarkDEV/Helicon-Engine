#include "Renderer.h"
#include <stdexcept>


void Renderer::createVkInstance() {
    if (enableValidationLayers && !m_validationHelper.checkValidationLayerSupport()) {
        throw std::runtime_error("Validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = m_validationHelper.getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        m_validationHelper.populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }

     if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }
}

bool Renderer::Initialize(HWND hwnd) {
    createVkInstance();

    m_validationHelper.setupDebugMessenger(m_vkInstance, m_debugMessenger);

    return true;
}

void Renderer::Shutdown() {

    m_validationHelper.clear(m_vkInstance, m_debugMessenger);

    clearVkInstance();
  
}

IRenderer* hcCreateRenderer() {
    return new Renderer();
}

void Renderer::clearVkInstance() {
    if (m_vkInstance != VK_NULL_HANDLE) {
        vkDestroyInstance(m_vkInstance, nullptr);
    }
}
