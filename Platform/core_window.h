#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#elif defined(__linux__)
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
#else
    #error "Unsupported platform"
#endif

#include "../Core/types.h"

#define CORE_WINDOW_WIDTH 1280
#define CORE_WINDOW_HEIGHT 720

enum class window_backend
{
    Win32,
    X11
};

struct core_window
{
    window_backend backend;
    union
    {
#ifdef _WIN32
        struct
        {
            HWND hwnd = nullptr;
            HINSTANCE hinstance = nullptr;
            bool should_close = false;
            HBITMAP splash_image = nullptr;
        } win32;
#else
        struct
        {
            Display* display = nullptr;
            Window window = 0;
            Atom wm_elete;
            bool should_close = false;
        } x11;
#endif
    };
};

// Cross platform API
bool core_initialize_window(core_window& window, window_backend backend, i32 width, i32 height, const char* title);
void core_poll_events(core_window& window);
void core_shutdown_window(core_window& window);
bool core_window_should_close(const core_window& window);

// Platform specific (internal)
#ifdef _WIN32
static bool core_initialize_win32(core_window& window, i32 width, i32 height, const char* title);
static void core_poll_events_win32(core_window& window);
static void core_shutdown_win32(core_window& window);
#elif defined(__linux__)
static bool core_initialize_x11(core_window& window, i32 width, i32 height, const char* title);
static void core_poll_events_x11(core_window& window);
static void core_shutdown_x11(core_window& window);
#endif