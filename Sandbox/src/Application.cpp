#include "Application.h"
#include <iostream>
#include <Windows.h>

namespace Helicon
{
    bool Application::LaunchCoreSystems()
    {
        HINSTANCE hInstance = GetModuleHandle(nullptr);

        if (!m_Window.Initialize(hInstance, 1280, 720, "Helicon Engine"))
        {
            throw std::runtime_error("Failed to initialize Win32 window!");
        }

        // Later can pass m_Window.GetHWND() into the Vulkan renderer
        // e.g m_renderer->hcInitializeRenderer(m_Window.GetHWND());
        m_renderer->hcInitializeRenderer();

        return HC_SUCCESS;
    }

    bool Application::LaunchModules()
    {
        return HC_SUCCESS;
    }

    void Application::GameLoop()
    {
        while (!m_Window.ShouldClose())
        {
            m_Window.PollEvents();

            // m_renderer->RenderFrame();
        }

        m_Window.Shutdown();
    }

    void Application::ShutdownModules()
    {
    }

    void Application::ShutdownCoreSystems()
    {
    }
}