#include "Application.h"

namespace Helicon
{
	bool Application::hcLaunchCoreSystems()
	{
		if (enableEngineLogger) {
			if (Logger::hcInitializeEngineLogger() != HC_SUCCESS) {
				throw std::runtime_error("Failed tto initialize the engine logger!");
			}
		}

		if (m_HcWindow.hcInitializeWindow() != HC_SUCCESS) {
			throw std::runtime_error("Failed to initialize the window!");
		}

		return HC_SUCCESS;
	}

	bool Application::hcLaunchModules()
	{

		return HC_SUCCESS;
	}


	void Application::hcGameLoop()
	{

	}


	void Application::hcShutdownModules()
	{

	}

	void Application::hcShutdownCoreSystems()
	{

	}
}

