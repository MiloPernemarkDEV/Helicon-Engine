#include "Application.h"
#include "VectormathTesting.h"

int main ()
{
	
	// testing Vec3 ops
	VMathTests::RunVec3Tests();

	// main loop
	Application app;

	if (app.Launch() == Application::InitResult::Error)
	{
		return 1;
	}

	app.Run();

	app.End();


	return 0;
}