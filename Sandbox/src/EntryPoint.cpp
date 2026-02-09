// We want to seperate engine from the actual game 
// Here we will start up the game
// Start up the systems 
// End the game 
// End the systems 

#include "Application.h"

int main ()
{
	Application app;

	if (!app.Launch() == true)
	{
		return 1;
	}
	
	app.Run();

	app.End();

	return 0;
}