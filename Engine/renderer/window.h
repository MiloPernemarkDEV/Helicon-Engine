//////////////
// Window.h //
//////////////

// 2026-02-10 - Milo
// Filename changed from window.h -- to Window.h
// Added class to Helicon namespace


#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include "../core/DllDefines.h"
#include "../core/Logger.h" 
#include "../core/ICoreSystem.h"

namespace Helicon 
{
    class ENGINE_API Window : ICoreSystem
    {

    public:
        Window();
        ~Window();

        bool Init();
        void SetContext();
        bool Create();

        void Terminate();

        bool ShouldCloseWindow();
        void ProcessEvents();
        void SwapBuffers();
        void SetWindowIcon(const char* path);

        void Shutdown();

        GLFWwindow* GetGLFWwindow() const { return m_Window; }

        int GetWidth() const { return WINDOW_WIDTH; }
        int GetHeight() const { return WINDOW_HEIGHT; }

    private:
        GLFWwindow* m_Window;
        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;
    };
}

