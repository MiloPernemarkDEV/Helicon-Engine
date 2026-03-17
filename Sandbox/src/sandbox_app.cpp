#include "sandbox_app.h"

bool app_launch(sandbox_app* app, const char* title)
{
    return core_initialize_window(app->core_window, app->core_window.backend,
        CORE_WINDOW_WIDTH, CORE_WINDOW_HEIGHT, title);
}

void app_game_loop(sandbox_app* app)
{
    while (!core_window_should_close(app->core_window)) {
        core_poll_events(app->core_window);
    }
}

void app_shutdown(sandbox_app* app)
{
    core_shutdown_window(app->core_window);
}
