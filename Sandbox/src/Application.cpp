#include "Application.h"
#include <iostream>
#include <Windows.h>

namespace Helicon
{
    bool Application::LaunchCoreSystems()
    {
        HINSTANCE hInstance = GetModuleHandle(nullptr);
        if (!m_Window.Initialize(hInstance, HC_WINDOW_WIDTH, HC_WINDOW_HEIGHT, "Banana Farming Simulator:"))
        {
            throw std::runtime_error("Failed to initialize Win32 window!");
        }
        

        if (!m_renderer->Initialize(m_Window.GetHWND())) 
        {
            throw std::runtime_error("Failed to initialize the renderer!");

        }



        return true;
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