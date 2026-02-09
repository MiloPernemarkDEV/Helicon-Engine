#include "Application.h"

Application::InitResult Application::Launch()
{

	Helicon::Logger::Init();

	if (!m_Window.Init()) 
	{
		return InitResult::Error;
		HEL_ERROR("Failed to initialize window.");
	}

	m_CoreTime.Init();

	return InitResult::Success;
}

void Application::Run()
{

	while (!m_Window.ShouldCloseWindow())
	{
		m_CoreTime.Update();
		m_Window.ProcessEvents();
	}
}

void Application::End()
{

	m_CoreTime.Shutdown();
	m_Window.Shutdown();
}
