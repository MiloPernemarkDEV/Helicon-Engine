#pragma once

#include "Defines.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>
#include <stdint.h>

static constexpr uint32_t HC_WINDOW_WIDTH = 1280;
static constexpr uint32_t HC_WINDOW_HEIGHT = 720;

class ENGINE_API HcWin32Window
{
public:
    bool Initialize(HINSTANCE hInstance, int width, int height, const char* title);
    void PollEvents();
    void Shutdown();

    bool ShouldClose() const { return m_shouldClose; }
    HWND GetHWND() const { return m_hWnd; }

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND      m_hWnd = nullptr;
    HINSTANCE m_hInstance = nullptr;
    bool      m_shouldClose = false;


};