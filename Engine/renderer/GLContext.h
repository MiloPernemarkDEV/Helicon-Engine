#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"


class GLContext
{
public:
    GLContext(GLFWwindow* window);

    void Load();
private:
    GLFWwindow* m_Window;
};
