#include "Application.h"

int main ()
{
	Helicon::Application app;

	if (app.hcLaunchCoreSystems() != HC_SUCCESS) {
		throw std::runtime_error("Failed to launch core systems");
	}

	if (app.hcLaunchModules() != HC_SUCCESS)
	{
		throw std::runtime_error("Failed to launch modules");
	}
	
	app.hcGameLoop();	

	app.hcShutdownModules();

	app.hcShutdownCoreSystems();

	return EXIT_SUCCESS;
}