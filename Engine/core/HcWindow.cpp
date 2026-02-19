#include "HcWindow.h"

bool HcWindow::hcInitializeWindow()
{
	glfwInit();
	return HC_SUCCESS;
}

void HcWindow::hcShutdownWindow()
{
	glfwDestroyWindow(m_Window);
}

void HcWindow::hcPollEvents()
{
	glfwPollEvents();
}
