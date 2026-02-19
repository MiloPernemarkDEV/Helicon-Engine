#pragma once


#include "Helicon.h"
#include "GLFW/glfw3.h"
#include <stdexcept>

namespace Helicon
{

	class Application
	{
	public:

		Application() = default;

		bool hcLaunchCoreSystems();

		bool hcLaunchModules();

		void hcGameLoop();

		void hcShutdownModules();

		void hcShutdownCoreSystems();

	private:
		HcWindow m_HcWindow;
	};
}





