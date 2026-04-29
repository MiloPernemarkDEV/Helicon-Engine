#pragma once

#include <render_interface.h>
#include "app_config.h"
#include "engine_config.h"
#include "engine_arena.h"

#include <GLFW/glfw3.h>



struct Application
{
	AppConfig app_config{};
	RendererInterface* renderer_interface{};
	GLFWwindow* game_window = nullptr;

	Application() = default;
};

bool application_init(Application* app, Arena* frame_storage);

void application_run(Application* app, Arena* frame_storage);

void application_end(Application* app);





