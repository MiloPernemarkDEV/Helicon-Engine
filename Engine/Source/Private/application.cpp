#include "application.h"
#include "engine_config.h"
#include "engine_arena.h"

bool application_init(Application* app, Arena* global_storage) { 
	glfwInit();

	if (!app) {
		return false;
	}

	app_config_init(&app->app_config);

	app->game_window = glfwCreateWindow(app->app_config.height, app->app_config.width,
		app->app_config.title,nullptr, nullptr);
	
	app->renderer_interface = engine_allocate<RendererInterface>(global_storage);
	renderer_init(app->game_window, app->renderer_interface);

	if (!app->renderer_interface) {
		return false;
	}

	return true;
}

void application_run(Application* app, Arena* frame_arena)
{
	RT_ASSERT(frame_arena != nullptr, "Frame arena is nullptr");

	while (!glfwWindowShouldClose(app->game_window)) {
		float deltaTime = 0;
		renderer_draw_frame(app->game_window, app->renderer_interface, deltaTime);
		
		renderer_swap_buffers(app->game_window);
		renderer_poll_events();


		engine_reset_arena(frame_arena);
	}
}

void application_end(Application* app)
{
	renderer_cleanup();
}
