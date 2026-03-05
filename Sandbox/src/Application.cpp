#include "Application.h"
#include <iostream>
#include <chrono> 
#include <thread>

namespace Helicon
{
    Application::~Application()
    {
        if (!hasShutModules_) 
        {
            ShutdownModules();
        }

        if (!hasShutCore_) 
        {
            ShutdownCore();
        }
    }

    bool Application::LaunchCoreSystems()
    {
        hInstance_ = GetModuleHandle(nullptr);

        if (!window_.Initialize(hInstance_, HC_WINDOW_WIDTH, HC_WINDOW_HEIGHT, "Banana Farming Simulator")) 
        {
            return false;
        }
            
        if (!renderer_->Initialize(window_.GetHWND(), window_.GetHInstance()))
        {
            return false;
        }
           
        window_.DestroyLaunchWindow();

        return true;
    }

    bool Application::LaunchModules()
    {
        return HC_SUCCESS;
    }

    void Application::GameLoop()
    {
        while (!window_.ShouldClose())
        {
            window_.PollEvents();

            // m_renderer->RenderFrame();
        }
    }

    // shutdown module & core systems in reverse order 
    void Application::ShutdownModules()
    {
     

        hasShutModules_ = true;
    }

    void Application::ShutdownCore()
    {
        if (renderer_) {
            renderer_->Shutdown(); 
        }

        window_.Shutdown(); 

        hasShutCore_ = true;
    }
}