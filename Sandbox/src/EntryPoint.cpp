#include "Application.h"
	
#include <iostream>


int main ()
{
	Helicon::Application app;

	try {
		if (!app.LaunchCoreSystems())
		{
			throw std::runtime_error("Failed to launch core systems");
		}

		if (!app.LaunchModules())
		{
			throw std::runtime_error("Failed to launch modules");
		}

		app.GameLoop();

		app.ShutdownModules();

		app.ShutdownCore();
	}
	catch (std::exception& e) {
		std::cerr << "Exception thrown: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	

	return EXIT_SUCCESS;
}