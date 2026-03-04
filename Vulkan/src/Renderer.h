#pragma once
#include "IRenderer.h"
#include "Validation.h"
#include "Device.h"

class Renderer : public IRenderer {
public:
    bool Initialize(HWND hwnd) override;
    void Shutdown() override;
    VkInstance GetVkInstance() const { return vkInstance_; }

private:
    void createVkInstance();
    void clearVkInstance();

    void populateInstanceCreateInfo(
        VkInstanceCreateInfo& createInfo,
        VkApplicationInfo& appInfo,
        VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);

    std::vector<const char*> extensions_;

    // Vulkan core
    VkInstance vkInstance_ = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    Device deviceHelper_;


    // Validation / Debugging
    Validation validationHelper_;
    VkDebugUtilsMessengerEXT debugMessenger_ = VK_NULL_HANDLE;

};
