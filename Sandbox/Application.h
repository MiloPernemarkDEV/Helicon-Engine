#pragma once

#include "window.h"
#include "coreTime.h"
#include <iostream>

// We are not using the constructors for initializing the sytems because
// it is hard to be sure the systems initilize in the correct order in constructor/destructor
// therefore we state the correct order inside the member functions instead 
// some systems might depend on eachother thats why this is important 

// Explore using a enum for error handling the initialized system if something in the system fails 

class Application
{
public:
	Application();

	// Initialize systems in correct order and flag if they cant initialize
	bool Launch();

	// Game loop
	void Run();

	// Shutdown sytems in reverse order
	void End();

private:
	// add the systems as member variables 
	window m_Window;
	
};

