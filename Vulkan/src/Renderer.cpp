#include "Renderer.h"
#include <stdexcept>
#include "Instance.h"

// Each wrapper class owns exactly one Vulkan object.
// Every wrapper provides a getter for its underlying handle.
// If a wrapper depends on another Vulkan object:
// Store a pointer or reference to the corresponding wrapper.
// Pass any required handles via the wrapper's getter in the constructor or setup.

Renderer::Renderer()
    :instance_(validation_, extensions_)
{
}

bool Renderer::Initialize(HWND hWnd, HINSTANCE hInstance)
{
    auto requiredExtensions = validation_.getRequiredExtensions();
    instance_.setExtensions(requiredExtensions);

    instance_.setup();

    validation_.setup(instance_.getInstance());
    return true;
}

void Renderer::Shutdown() 
{


    validation_.destroy(instance_.getInstance());
    instance_.destroy();
}

std::unique_ptr<IRenderer> CreateVulkanRenderer() 
{
    return std::make_unique<Renderer>();
}

