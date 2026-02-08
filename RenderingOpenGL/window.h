#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>
#include "dllDefines.h"



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
    static void glfwShutDown();

    GLFWwindow* GetGLFWwindow() const { return m_Window; }

    int GetWidth() const { return windowWidth; }
    int GetHeight() const { return windowHeight; }

private:
    GLFWwindow* m_Window;
    const int windowWidth;
    const int windowHeight;
};
