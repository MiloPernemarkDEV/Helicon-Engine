#pragma once

#include "core/Defines.h"
#include "core/HcWin32Window.h"
#include <stdexcept>
#include "IRenderer.h"
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


namespace Helicon
{
    class Application
    {
    public:
        Application() = default;
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        ~Application();
        
        bool LaunchCoreSystems();
        bool LaunchModules();

        void GameLoop();

        void ShutdownModules();
        void ShutdownCore();

    private:
        HINSTANCE hInstance_;
        HcWin32Window window_;
        std::unique_ptr<IRenderer> renderer_ = CreateVulkanRend();
        bool hasShutCore_ = false;
        bool hasShutModules_ = false;
    };
}