#pragma once

#include "IRenderer.h"
#include "RendDefines.h"


#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX 
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

namespace rend
{
	using i32 = int32_t;
	using u32 = uint32_t;

#ifdef _DEBUG 
	constexpr bool enableValidationLayers = true;
#else 
#define 
	constexpr bool enableValidationlayers = false;
#endif

	const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
	};

class RENDERER_API Renderer : public IRenderer
{
public:
	void hcInitializeRenderer();
	void Shutdown();
	

private:
	void createVkInstance();
	void checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();


	// Members 
	VkInstance m_vkInstance = VK_NULL_HANDLE;
};

} // namespace rend



