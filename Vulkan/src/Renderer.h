#pragma once
#include "IRenderer.h"
#include "Validation.h"

class Renderer : public IRenderer {
public:
    bool Initialize(HWND hwnd) override;
    void Shutdown() override;
    VkInstance GetVkInstance() const { return m_vkInstance; }

private:
    void createVkInstance();
    void clearVkInstance();

    VkInstance m_vkInstance = VK_NULL_HANDLE;

    // Validation
    VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
    Validation m_validationHelper; 

    // Device
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;

};
