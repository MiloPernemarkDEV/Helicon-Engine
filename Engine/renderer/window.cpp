#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Window.h"

namespace Helicon
{
    Window::Window()
        : m_Window(nullptr), WINDOW_WIDTH(800), WINDOW_HEIGHT(800)
    {
    }

    Window::~Window()
    {
        Terminate();
    }

    bool Window::Init()
    {
        glfwInit();
        SetContext();

        if (!Create())
        {
            return false;
        }

        glfwMakeContextCurrent(m_Window);

        SetWindowIcon("../Engine/assets/Icons/icon.png");

        HE_LOG_DEBUG("Window Init.");
        return true;
    }

    void Window::SetContext()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

    bool Window::Create()
    {
        m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sandbox Project", NULL, NULL);

        return (m_Window != nullptr);
    }

    void Window::Terminate()
    {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
        }
    }

    bool Window::ShouldCloseWindow()
    {
        return m_Window && glfwWindowShouldClose(m_Window);
    }

    void Window::ProcessEvents()
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers()
    {
        if (m_Window)
            glfwSwapBuffers(m_Window);
    }

    void Window::Shutdown()
    {
        if (m_Window)
            glfwDestroyWindow(m_Window);

        glfwTerminate();
        HE_LOG("Window shutdown.");
    }

    void Window::SetWindowIcon(const char* path)
    {
        GLFWimage image;
        int width, height, channels;

        unsigned char* pixels = stbi_load(path, &width, &height, &channels, 4);
        if (!pixels)
        {
            return;
        }

        image.width = width;
        image.height = height;
        image.pixels = pixels;

        glfwSetWindowIcon(m_Window, 1, &image);

        stbi_image_free(pixels);
    }
}


