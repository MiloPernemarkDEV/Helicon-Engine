#include "Application.h"

Application::Application()
{

}

bool Application::Launch()
{
	if (!m_Window.Init()) 
	{
		return false;
	}

	return true;
}

void Application::Run()
{

	// coreTime::Init();

	while (!m_Window.ShouldCloseWindow())
	{
		// coreTime::Update();
		m_Window.ProcessEvents();
	}
}

void Application::End()
{



	window::glfwShutDown();
}
