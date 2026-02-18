#include "Application.h"

int main ()
{
	Application app;

	if (app.LaunchCoreSystems() == Application::LaunchState::Error)
	{
		return EXIT_FAILURE;
	}

	if (app.LaunchModules() == Application::LaunchState::Error)
	{
		return EXIT_FAILURE;
	}
	
	app.RunGame();	

	app.ShutdownModules();

	app.ShutdownCoreSystems();

	return EXIT_SUCCESS;
}