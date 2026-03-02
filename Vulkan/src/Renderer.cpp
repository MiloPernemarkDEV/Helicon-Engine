#include "Renderer.h"
#include <stdexcept>

#include <iostream>

namespace rend
{
	void Renderer::createVkInstance() {

		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Hello Triangle";
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pEngineName = "No Engine";
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		if (vkCreateInstance(&create_info, nullptr, &m_vkInstance) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Vulkan instance!");
		}
	}

	bool checkValidationLayerSupport() {
		uint32_t layer_count;
		vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

		std::vector<VkLayerProperties> available_layers(layer_count);
		vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

		for (const char* layer_name : validationLayers) {
			bool layer_found = false;
			for (const auto& layer_properties : available_layers) {
				if (strcmp(layer_name, layer_properties.layerName) == 0) {
					layer_found = true;
					break;
				}
			}
			if (!layer_found) return false;
		}
		return true;
	}

	std::vector<const char*> Renderer::getRequiredExtensions() {
		u32 glfw_extension_count = 0;

		const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

		std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);

		if (enableValidationLayers)
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		return extensions;
	}

	IRenderer* hcCreateRenderer()
	{
		return new Renderer();
	}

	void Renderer::hcInitializeRenderer()
	{
		createVkInstance();
		std::cout << "Renderer: initialized!";
	}

	void Renderer::Shutdown()
	{
		// destroy instance etc.
	}

} // namespace rend





