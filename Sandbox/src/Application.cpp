#include "Application.h"


Application::LaunchState Application::LaunchCoreSystems()
{

#ifdef _DEBUG // might be bad to remove logs from release build 

	if (!Helicon::Logger::Init())
	{
		HE_LOG_ERROR("Failed to initialize logger");
		return LaunchState::Error;
	}

#endif

	if (!m_Window.Init()) 
	{
		HE_LOG_ERROR("Failed to initialize window.");
		return LaunchState::Error;
	}

	if (!m_Time.Init())
	{
		HE_LOG_ERROR("Failed to initialize Time");
		return LaunchState::Error;
	}

	return LaunchState::Success;
}

Application::LaunchState Application::LaunchModules()
{

	return LaunchState::Success;
}


void Application::RunGame()
{

	while (!m_Window.ShouldCloseWindow())
	{
		m_Time.Update();
		m_Window.ProcessEvents();
	}
}


void Application::ShutdownModules()
{

}

void Application::ShutdownCoreSystems()
{


	m_Time.Shutdown();
	m_Window.Shutdown();
	Helicon::Logger::Shutdown();
}
