#include "window.h"

window::window()
    : m_Window(nullptr), WINDOW_WIDTH(800), WINDOW_HEIGHT(800)
{
}

window::~window()
{
    Terminate();
}

bool window::Init()
{
    glfwInit();
    SetContext();
 
    if (!Create())
    {
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    return true;
}

void window::SetContext()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

bool window::Create()
{
    m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "USS-CALLIOPE", NULL, NULL);
    
    return (m_Window != nullptr);
}

void window::Terminate()
{
    if (m_Window) {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr; 
    }
}

bool window::ShouldCloseWindow()
{
    return m_Window && glfwWindowShouldClose(m_Window);
}

void window::ProcessEvents()
{
    glfwPollEvents();
}

void window::SwapBuffers()
{
    if (m_Window)
        glfwSwapBuffers(m_Window);
}

void window::glfwShutDown()
{
    glfwTerminate();
}
