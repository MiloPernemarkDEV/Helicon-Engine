#include "Application.h"

Application::InitResult Application::Launch()
{

	Helicon::Logger::Init();

	if (!m_Window.Init()) 
	{
		HEL_ERROR("Launch Failed.");
		return InitResult::Error;
	}

	m_CoreTime.Init();

	HEL_INFO("launch Complete.");
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

	HEL_INFO("Shutdown Complete.");

	// Shutdown logger
}
