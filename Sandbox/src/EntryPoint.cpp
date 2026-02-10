#include "Application.h"
//#include "VectormathTesting.h"
#include <memory>

int main ()
{
	
	
	std::unique_ptr<Application> app = std::make_unique<Application>();

	if (app->Launch() == Application::InitResult::Error)
	{
		return 1;
	}
	
	app->Run();

	app->End();


	return 0;
}