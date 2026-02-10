#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

    SetWindowIcon("../Engine/assets/Icons/icon.png");

    HEL_DEBUG("Window Init called");
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
    m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BOY BAND BATTLES", NULL, NULL);
    
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

void window::Shutdown()
{
    if (m_Window)
        glfwDestroyWindow(m_Window);

    glfwTerminate();
    HEL_DEBUG("Shutdown window.");
}

void window::SetWindowIcon(const char* path)
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

