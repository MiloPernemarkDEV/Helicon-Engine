#include "GLContext.h"

GLContext::GLContext(GLFWwindow* window)
    : m_Window(window)
{
    
}

void GLContext::Load()
{
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGL())
        return;

    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    glViewport(0, 0, width, height);
}

