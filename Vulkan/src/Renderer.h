#pragma once
#include "IRenderer.h"
#include "Validation.h"
#include "Device.h"
#include "HandleManager.h"

class Renderer : public IRenderer {
public:
    bool Initialize(HWND hwnd, HINSTANCE hInstance) override;
    void Shutdown() override;
    VkInstance GetVkInstance() const { return handles.vkInstance_; }

private:
    void createVkInstance();
    void clearVkInstance();

    void populateInstanceCreateInfo(
        VkInstanceCreateInfo& createInfo,
        VkApplicationInfo& appInfo,
        VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo);

    std::vector<const char*> extensions_;

    HandleManager handles;
    Device deviceHelper;
    Validation validationHelper;
};
