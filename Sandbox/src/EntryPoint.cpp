#include "Application.h"

int main ()
{
	Application app;

	if (app.Launch() == Application::InitResult::Error)
	{
		return 1;
	}

	app.Run();

	app.End();

	return 0;
}