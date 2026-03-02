#pragma once

#include "core/Defines.h"
#include "core/HcWin32Window.h"
#include <stdexcept>
#include "IRenderer.h"
#include <Windows.h>

namespace Helicon
{
    class Application
    {
    public:
        Application() = default;

        bool LaunchCoreSystems();
        bool LaunchModules();

        void GameLoop();

        void ShutdownModules();
        void ShutdownCoreSystems();

    private:
        HcWin32Window m_Window;
        rend::IRenderer* m_renderer = rend::hcCreateRenderer();
    };
}