#pragma once

#include "Platform/core_window.h"
#include <minwindef.h>

#define HELICON_RENDERER_USE_VULKAN
#include "Renderer/renderer.h"    

struct sandbox_app
{
    core_window core_window;
    HINSTANCE hinstance;
};

bool app_launch(struct sandbox_app* app, const char* title);
void app_game_loop(struct sandbox_app* app);
void app_shutdown(struct sandbox_app* app);