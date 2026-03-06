#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

#ifdef _DEBUG
static constexpr bool enableValidationLayers = true;
#else
static constexpr bool enableValidationLayers = false;
#endif

class Validation
{
public:
    Validation() = default;
    ~Validation() = default;

    bool checkValidationLayerSupport() const;
    std::vector<const char*> getRequiredExtensions() const;
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& create_info) const;

    void setup(VkInstance instance);
    void destroy(VkInstance instance);

    VkDebugUtilsMessengerEXT getMessenger() const { return debugMessenger_; }
    const std::vector<const char*>& getValidationlayers() const {return validationLayers_; }


private:
    VkDebugUtilsMessengerEXT debugMessenger_ = VK_NULL_HANDLE;
    VkInstance instance_ = VK_NULL_HANDLE; 

    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    inline static const std::vector<const char*> validationLayers_ = {
      "VK_LAYER_KHRONOS_validation"
    };
};




