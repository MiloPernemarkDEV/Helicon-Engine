#include "Application.h"
	

int main ()
{
	Helicon::Application app;

	if (app.LaunchCoreSystems() != HC_SUCCESS) {
		throw std::runtime_error("Failed to launch core systems");
	}

	if (app.LaunchModules() != HC_SUCCESS)
	{
		throw std::runtime_error("Failed to launch modules");
	}
	
	app.GameLoop();	

	app.ShutdownModules();

	app.ShutdownCoreSystems();

	return EXIT_SUCCESS;
}