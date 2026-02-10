#include "Application.h"
//#include "VectormathTesting.h"
//#include <memory>

int main ()
{

	std::unique_ptr<Application> app = std::make_unique<Application>();

	if (app->LaunchCoreSystems() == Application::LaunchState::Error)
	{
		return 1;
	}

	if (app->LaunchModules() == Application::LaunchState::Error)
	{
		return 1;
	}
	
	app->RunGame();	

	app->ShutdownModules();

	app->ShutdownCoreSystems();

	return 0;
}