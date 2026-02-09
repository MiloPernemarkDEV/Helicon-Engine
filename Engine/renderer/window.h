#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include "../core/dllDefines.h"



class ENGINE_API window
{
public:
    window();
    ~window();

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
