#include "app_config.h"
#include <GLFW/glfw3.h>

#include <stdexcept>


void app_config_init(AppConfig* config)
{
	if (!config) {
		throw std::runtime_error("app config is nullptr!");
	}

	config->height = 800;
	config->width = 800;
	config->title = "Game";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
