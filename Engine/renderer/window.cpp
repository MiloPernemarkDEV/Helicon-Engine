#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Window.h"


Helicon::Window::Window()
: m_Window(nullptr), WINDOW_WIDTH(800), WINDOW_HEIGHT(800)
{
}

Helicon::Window::~Window()
{
Terminate();
}

bool Helicon::Window::Init()
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

void Helicon::Window::SetContext()
{
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

bool Helicon::Window::Create()
{
m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sandbox Project", NULL, NULL);
    
return (m_Window != nullptr);
}

void Helicon::Window::Terminate()
{
if (m_Window) {
    glfwDestroyWindow(m_Window);
    m_Window = nullptr; 
}
}

bool Helicon::Window::ShouldCloseWindow()
{
return m_Window && glfwWindowShouldClose(m_Window);
}

void Helicon::Window::ProcessEvents()
{
glfwPollEvents();
}

void Helicon::Window::SwapBuffers()
{
if (m_Window)
    glfwSwapBuffers(m_Window);
}

void Helicon::Window::Shutdown()
{
if (m_Window)
    glfwDestroyWindow(m_Window);

glfwTerminate();
HEL_DEBUG("Shutdown window.");
}

void Helicon::Window::SetWindowIcon(const char* path)
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

